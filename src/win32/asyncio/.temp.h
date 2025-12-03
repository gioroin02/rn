
    // eventloop.h (interfaccia semplificata solo per accept e connect, ora con struct EventLoop)
#pragma once
#include <stdint.h>
#include <stddef.h>

typedef enum {
    EV_ACCEPT    = 1 << 0,
    EV_CONNECT   = 1 << 1,
    EV_ERROR     = 1 << 2
} event_type_t;

typedef struct {
    int            fd;        // per accept: client fd, per connect: il fd connesso
    event_type_t   type;
    void*          userdata;
} event_t;

typedef struct EventLoop EventLoop;  // opaca

// Crea un nuovo event loop
EventLoop* eventloop_create(void);

// Distrugge
void eventloop_destroy(EventLoop* loop);

// Aggiunge un socket per accept o connect
int eventloop_add(EventLoop* loop, int fd, event_type_t events, void* userdata);

// Rimuove
int eventloop_del(EventLoop* loop, int fd);

// Poll: riempie events[] con completions pronti
// timeout_ms = -1 blocca, 0 non blocca
int eventloop_poll(EventLoop* loop, event_t* events, int max_events, int timeout_ms);

// Funzioni async (chiamale dopo add)
void async_accept(EventLoop* loop, int listen_fd);
void async_connect(EventLoop* loop, int fd, struct sockaddr* addr, int addrlen);
