// eventloop_iocp.c (implementazione semplificata solo accept + connect, senza statiche globali)
#define _WIN32_WINNT 0x0601
#include "eventloop.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

// Struttura per operazioni
typedef struct op_t {
    OVERLAPPED overlapped;
    int        fd;
    event_type_t type;  // ACCEPT o CONNECT
    void*      userdata;
    char       accept_buf[1024];  // per AcceptEx
    SOCKET     client_sock;       // per accept
} op_t;

// Per socket info
typedef struct {
    void* userdata;
} socket_info_t;

// Struttura interna per EventLoop
struct EventLoop {
    HANDLE iocp;
    event_t* ready_events;
    int ready_count;
    int ready_capacity;
    socket_info_t* socket_infos;
    int socket_capacity;
};

// Crea
EventLoop* eventloop_create(void) {
    EventLoop* loop = calloc(1, sizeof(EventLoop));
    if (!loop) return NULL;

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        free(loop);
        return NULL;
    }

    loop->iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (!loop->iocp) {
        free(loop);
        return NULL;
    }

    return loop;
}

// Distrugge
void eventloop_destroy(EventLoop* loop) {
    if (!loop) return;
    if (loop->iocp) CloseHandle(loop->iocp);
    free(loop->ready_events);
    free(loop->socket_infos);
    free(loop);
    WSACleanup();
}

// Assicura spazio per socket info
static void ensure_socket_info(EventLoop* loop, int fd) {
    if (fd >= loop->socket_capacity) {
        int new_cap = fd + 64;
        loop->socket_infos = realloc(loop->socket_infos, new_cap * sizeof(socket_info_t));
        for (int i = loop->socket_capacity; i < new_cap; ++i) loop->socket_infos[i].userdata = NULL;
        loop->socket_capacity = new_cap;
    }
}

// Aggiunge socket a IOCP
int eventloop_add(EventLoop* loop, int fd, event_type_t events, void* userdata) {
    if (!loop) return -1;
    ensure_socket_info(loop, fd);
    loop->socket_infos[fd].userdata = userdata;
    if (!CreateIoCompletionPort((HANDLE)(uintptr_t)fd, loop->iocp, 0, 0)) return -1;
    return 0;
}

int eventloop_del(EventLoop* loop, int fd) {
    if (!loop || fd >= loop->socket_capacity) return -1;
    loop->socket_infos[fd].userdata = NULL;
    // Nota: per cancellare ops pending, usa CancelIoEx se necessario
    return 0;
}

// Async accept
void async_accept(EventLoop* loop, int listen_fd) {
    if (!loop) return;
    op_t* op = calloc(1, sizeof(op_t));
    op->fd = listen_fd;
    op->type = EV_ACCEPT;
    op->userdata = loop->socket_infos[listen_fd].userdata;
    op->client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  // assumi IPv4

    DWORD bytes;
    BOOL res = AcceptEx((SOCKET)listen_fd, op->client_sock, op->accept_buf, 0,
                        sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
                        &bytes, &op->overlapped);
    if (!res && WSAGetLastError() != ERROR_IO_PENDING) {
        closesocket(op->client_sock);
        free(op);
    }
}

// Async connect
void async_connect(EventLoop* loop, int fd, struct sockaddr* addr, int addrlen) {
    if (!loop) return;
    op_t* op = calloc(1, sizeof(op_t));
    op->fd = fd;
    op->type = EV_CONNECT;
    op->userdata = loop->socket_infos[fd].userdata;

    // Bind a dummy addr per ConnectEx
    struct sockaddr_in dummy = {0};
    dummy.sin_family = AF_INET;
    bind((SOCKET)fd, (struct sockaddr*)&dummy, sizeof(dummy));

    // ConnectEx
    DWORD bytes;
    BOOL res = ConnectEx((SOCKET)fd, addr, addrlen, NULL, 0, &bytes, &op->overlapped);
    if (!res && WSAGetLastError() != ERROR_IO_PENDING) {
        free(op);
    }
}

// Poll (single-thread, blocca su GetQueued)
int eventloop_poll(EventLoop* loop, event_t* events, int max_events, int timeout_ms) {
    if (!loop) return -1;

    DWORD bytes = 0;
    ULONG_PTR key = 0;
    OVERLAPPED* ov = NULL;
    BOOL res = GetQueuedCompletionStatus(loop->iocp, &bytes, &key, &ov, (timeout_ms == -1 ? INFINITE : timeout_ms));

    if (ov) {
        op_t* op = (op_t*)ov;
        event_t ev = {0};
        ev.userdata = op->userdata;
        ev.type = op->type;

        if (op->type == EV_ACCEPT) {
            if (res) {
                // Update accept context
                setsockopt(op->client_sock, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
                           (char*)&op->fd, sizeof(op->fd));
                ev.fd = (int)op->client_sock;
            } else {
                ev.type |= EV_ERROR;
                ev.fd = op->fd;  // listen fd
                closesocket(op->client_sock);
            }
        } else if (op->type == EV_CONNECT) {
            ev.fd = op->fd;
            if (!res) ev.type |= EV_ERROR;
        }

        // Aggiungi a ready (semplice vector)
        if (loop->ready_count >= loop->ready_capacity) {
            loop->ready_capacity = loop->ready_capacity ? loop->ready_capacity * 2 : 64;
            loop->ready_events = realloc(loop->ready_events, loop->ready_capacity * sizeof(event_t));
        }
        loop->ready_events[loop->ready_count++] = ev;

        free(op);
    } else if (!res && GetLastError() == WAIT_TIMEOUT) {
        return 0;  // timeout, no eventi
    }

    // Copia a utente
    int n = (loop->ready_count > max_events) ? max_events : loop->ready_count;
    if (n > 0) {
        memcpy(events, loop->ready_events, n * sizeof(event_t));
        memmove(loop->ready_events, loop->ready_events + n, (loop->ready_count - n) * sizeof(event_t));
        loop->ready_count -= n;
    }
    return n;
}
