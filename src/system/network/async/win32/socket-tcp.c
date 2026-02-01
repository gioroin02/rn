#ifndef RHO_SYSTEM_NETWORK_ASYNC_WIN32_SOCKET_TCP_C
#define RHO_SYSTEM_NETWORK_ASYNC_WIN32_SOCKET_TCP_C

#include "socket-tcp.h"

static RBool32 rho_win32_io_queue_bind_socket_tcp(RWin32IoQueue* self, RWin32SocketTcp* socket)
{
    HANDLE handle = (HANDLE) socket->handle;
    HANDLE result = CreateIoCompletionPort(handle, self->handle, 0, 0);

    return result != NULL ? 1 : 0;
}

static RBool32 rho_win32_socket_tcp_begin_accept(RWin32SocketTcpAccept* task, RWin32IoQueue* queue)
{
    RWin32SocketTcp* self   = task->self;
    RWin32SocketTcp* value  = task->value;
    RUint8*          buffer = task->__buff__;
    RInt             size   = sizeof task->__buff__ / 2;

    if (rho_win32_io_queue_bind_socket_tcp(queue, value) == 0) return 0;

    rho_win32_io_queue_bind_socket_tcp(queue, self);

    BOOL status = WSAAcceptEx(self->handle, value->handle,
        buffer, 0, size, size, NULL, &task->overlap);

    if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static RIoEvent* rho_win32_socket_tcp_end_accept(RWin32SocketTcpAccept* task, RInt bytes, RMemoryArena* arena)
{
    RWin32SocketTcp* self  = task->self;
    RWin32SocketTcp* value = task->value;

    setsockopt(value->handle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
        (RChar8*) &self->handle, sizeof self->handle);

    RWin32AddrStorage storage = {0};
    RWin32Addr*       sockaddr = (RWin32Addr*) &storage;
    RInt              length   = sizeof storage;

    getsockname(value->handle, sockaddr, (int*) &length);

    value->storage = storage;

    RSocketTcpEvent* result =
        rho_memory_arena_reserve_of(arena, RSocketTcpEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_socket_tcp_event_accept(
        (RSocketTcp*) self, (RSocketTcp*) value, task->ctxt);

    return (RIoEvent*) result;
}

static RBool32 rho_win32_socket_tcp_begin_connect(RWin32SocketTcpConnect* task, RWin32IoQueue* queue)
{
    RWin32SocketTcp* self   = task->self;
    RHostIp          host   = task->host;
    RInt             length = 0;

    rho_win32_io_queue_bind_socket_tcp(queue, self);

    RWin32AddrStorage storage = rho_win32_addr_storage_make(
        host.address, host.port, &length);

    RWin32Addr* sockaddr = (RWin32Addr*) &storage;

    BOOL status = WSAConnectEx(self->handle, sockaddr, length,
        0, 0, NULL, &task->overlap);

    if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static RIoEvent* rho_win32_socket_tcp_end_connect(RWin32SocketTcpConnect* task, RInt bytes, RMemoryArena* arena)
{
    RWin32SocketTcp* self = task->self;
    RHostIp          host = task->host;

    // NOTE(Gio): This is useless but must not be null.
    RInt flag = 0;

    setsockopt(self->handle, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);

    RSocketTcpEvent* result =
        rho_memory_arena_reserve_of(arena, RSocketTcpEvent, 1);

    if (result == NULL) return NULL;

    BOOL status = WSAGetOverlappedResult(self->handle,
        &task->overlap, (DWORD*) &bytes, 0, (DWORD*) &flag);

    *result = rho_socket_tcp_event_connect(
        (RSocketTcp*) self, host, status, task->ctxt);

    return (RIoEvent*) result;
}

static RBool32 rho_win32_socket_tcp_begin_write(RWin32SocketTcpWrite* task, RWin32IoQueue* queue)
{
    RWin32SocketTcp* self   = task->self;
    RChar8*          pntr   = ((RChar8*) task->pntr) + task->start;
    RInt             size   = task->stop - task->start;
    WSABUF*          buffer = &task->buffer;

    rho_win32_io_queue_bind_socket_tcp(queue, self);

    buffer->buf = pntr;
    buffer->len = size;

    int status = WSASend(self->handle, buffer, 1, NULL, 0,
        &task->overlap, NULL);

    if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static RIoEvent* rho_win32_socket_tcp_end_write(RWin32SocketTcpWrite* task, RInt bytes, RMemoryArena* arena)
{
    RWin32SocketTcp* self  = task->self;
    RUint8*          pntr  = task->pntr;
    RInt             start = task->start;
    RInt             stop  = task->stop;

    RSocketTcpEvent* result =
        rho_memory_arena_reserve_of(arena, RSocketTcpEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_socket_tcp_event_write(
        (RSocketTcp*) self, pntr, start, stop, bytes, task->ctxt);

    return (RIoEvent*) result;
}

static RBool32 rho_win32_socket_tcp_begin_read(RWin32SocketTcpRead* task, RWin32IoQueue* queue)
{
    RWin32SocketTcp* self   = task->self;
    RChar8*          pntr   = ((RChar8*) task->pntr) + task->start;
    RInt             size   = task->stop - task->start;
    WSABUF*          buffer = &task->buffer;

    // NOTE(Gio): This parameter is useless but must not be null.
    RInt flag = 0;

    rho_win32_io_queue_bind_socket_tcp(queue, self);

    buffer->buf = pntr;
    buffer->len = size;

    int status = WSARecv(self->handle, buffer, 1, NULL, (DWORD*) &flag,
        &task->overlap, NULL);

    if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static RIoEvent* rho_win32_socket_tcp_end_read(RWin32SocketTcpRead* task, RInt bytes, RMemoryArena* arena)
{
    RWin32SocketTcp* self  = task->self;
    RUint8*          pntr  = task->pntr;
    RInt             start = task->start;
    RInt             stop  = task->stop;

    RSocketTcpEvent* result =
        rho_memory_arena_reserve_of(arena, RSocketTcpEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_socket_tcp_event_read(
        (RSocketTcp*) self, pntr, start, stop, bytes, task->ctxt);

    return (RIoEvent*) result;
}

RBool32 rho_win32_socket_tcp_async_accept(RWin32SocketTcp* self, RWin32SocketTcp* value, RWin32IoQueue* queue, void* ctxt)
{
    RHostIp host = rho_win32_socket_tcp_host(self);

    if (rho_win32_socket_tcp_create(value, host) == 0) return 0;

    RWin32SocketTcpAccept* result = rho_memory_pool_reserve_of(
        &queue->pool, RWin32SocketTcpAccept, 1);

    if (result != NULL) {
        rho_memory_set(result->__buff__, sizeof result->__buff__, 0x00);

        result->self      = self;
        result->value     = value;
        result->ctxt      = ctxt;
        result->overlap   = (OVERLAPPED) {0};
        result->callback  = rho_win32_socket_tcp_end_accept;
        result->list_next = NULL;

        if (rho_win32_socket_tcp_begin_accept(result, queue) != 0)
            return rho_win32_io_queue_submit(queue, (RWin32IoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

RBool32 rho_win32_socket_tcp_async_connect(RWin32SocketTcp* self, RHostIp host, RWin32IoQueue* queue, void* ctxt)
{
    if (rho_win32_socket_tcp_bind(self) == 0) return 0;

    RWin32SocketTcpConnect* result = rho_memory_pool_reserve_of(
        &queue->pool, RWin32SocketTcpConnect, 1);

    if (result != NULL) {
        result->self      = self;
        result->host      = host;
        result->ctxt      = ctxt;
        result->overlap   = (OVERLAPPED) {0};
        result->callback  = rho_win32_socket_tcp_end_connect;
        result->list_next = NULL;

        if (rho_win32_socket_tcp_begin_connect(result, queue) != 0)
            return rho_win32_io_queue_submit(queue, (RWin32IoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

RBool32 rho_win32_socket_tcp_async_write(RWin32SocketTcp* self, RUint8* pntr, RInt start, RInt stop, RWin32IoQueue* queue, void* ctxt)
{
    RWin32SocketTcpWrite* result = rho_memory_pool_reserve_of(
        &queue->pool, RWin32SocketTcpWrite, 1);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->overlap   = (OVERLAPPED) {0};
        result->callback  = rho_win32_socket_tcp_end_write;
        result->list_next = NULL;

        if (rho_win32_socket_tcp_begin_write(result, queue) != 0)
            return rho_win32_io_queue_submit(queue, (RWin32IoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

RBool32 rho_win32_socket_tcp_async_read(RWin32SocketTcp* self, RUint8* pntr, RInt start, RInt stop, RWin32IoQueue* queue, void* ctxt)
{
    RWin32SocketTcpRead* result = rho_memory_pool_reserve_of(
        &queue->pool, RWin32SocketTcpRead, 1);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->overlap   = (OVERLAPPED) {0};
        result->callback  = rho_win32_socket_tcp_end_read;
        result->list_next = NULL;

        if (rho_win32_socket_tcp_begin_read(result, queue) != 0)
            return rho_win32_io_queue_submit(queue, (RWin32IoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

#endif
