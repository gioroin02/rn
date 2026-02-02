#ifndef RHO_SYSTEM_NETWORK_LINUX_ASYNC_SOCKET_TCP_C
#define RHO_SYSTEM_NETWORK_LINUX_ASYNC_SOCKET_TCP_C

#include "socket-tcp.h"

static RBool32 rho_linux_io_queue_bind_socket_tcp(RLinuxIoQueue* self, RLinuxSocketTcp* socket, RLinuxIoTask* task)
{
    int handle = (int) socket->handle;
    int queue  = (int) self->handle;

    RLinuxEpollEvent notif = {0};

    notif.events   = EPOLLIN | EPOLLOUT;
    notif.data.ptr = task;

    // TODO(Gio): check if could encounter EINTR.

    int status = epoll_ctl(queue, EPOLL_CTL_ADD, handle, &notif);

    if (status == -1 && errno == EEXIST)
        status = epoll_ctl(queue, EPOLL_CTL_MOD, handle, &notif);

    return status != -1 ? 1 : 0;
}

static RBool32 rho_linux_socket_tcp_begin_accept(RLinuxSocketTcpAccept* task, RLinuxIoQueue* queue)
{
    RLinuxSocketTcp* self  = task->self;
    RLinuxSocketTcp* value = task->value;

    rho_linux_io_queue_bind_socket_tcp(queue,
        self, (RLinuxIoTask*) task);

    return 1;
}

static RIoEvent* rho_linux_socket_tcp_end_accept(RLinuxSocketTcpAccept* task, RMemoryArena* arena)
{
    RLinuxSocketTcp* self  = task->self;
    RLinuxSocketTcp* value = task->value;

    RBool32 status = rho_linux_socket_tcp_accept(self, value);

    if (status == 0) return NULL;

    RSocketTcpEvent* result =
        rho_memory_arena_reserve_of(arena, RSocketTcpEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_socket_tcp_event_accept(
        (RSocketTcp*) self, (RSocketTcp*) value, task->ctxt);

    return (RIoEvent*) result;
}

static RBool32 rho_linux_socket_tcp_begin_connect(RLinuxSocketTcpConnect* task, RLinuxIoQueue* queue)
{
    RLinuxSocketTcp* self = task->self;
    RHostIp          host = task->host;

    rho_linux_io_queue_bind_socket_tcp(queue,
        self, (RLinuxIoTask*) task);

    return 1;
}

static RIoEvent* rho_linux_socket_tcp_end_connect(RLinuxSocketTcpConnect* task, RMemoryArena* arena)
{
    RLinuxSocketTcp* self = task->self;
    RHostIp          host = task->host;

    RBool32 status = rho_linux_socket_tcp_connect(self, host);

    RSocketTcpEvent* result =
        rho_memory_arena_reserve_of(arena, RSocketTcpEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_socket_tcp_event_connect(
        (RSocketTcp*) self, host, status, task->ctxt);

    return (RIoEvent*) result;
}

static RBool32 rho_linux_socket_tcp_begin_write(RLinuxSocketTcpWrite* task, RLinuxIoQueue* queue)
{
    RLinuxSocketTcp* self = task->self;

    rho_linux_io_queue_bind_socket_tcp(queue,
        self, (RLinuxIoTask*) task);

    return 1;
}

static RIoEvent* rho_linux_socket_tcp_end_write(RLinuxSocketTcpWrite* task, RMemoryArena* arena)
{
    RLinuxSocketTcp* self  = task->self;
    RUint8*          pntr  = task->pntr;
    RInt             start = task->start;
    RInt             stop  = task->stop;

    RInt bytes = rho_linux_socket_tcp_write(self, pntr, start, stop);

    RSocketTcpEvent* result =
        rho_memory_arena_reserve_of(arena, RSocketTcpEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_socket_tcp_event_write(
        (RSocketTcp*) self, pntr, start, stop, bytes, task->ctxt);

    return (RIoEvent*) result;
}

static RBool32 rho_linux_socket_tcp_begin_read(RLinuxSocketTcpRead* task, RLinuxIoQueue* queue)
{
    RLinuxSocketTcp* self = task->self;

    rho_linux_io_queue_bind_socket_tcp(queue,
        self, (RLinuxIoTask*) task);

    return 1;
}

static RIoEvent* rho_linux_socket_tcp_end_read(RLinuxSocketTcpRead* task, RMemoryArena* arena)
{
    RLinuxSocketTcp* self  = task->self;
    RUint8*          pntr  = task->pntr;
    RInt             start = task->start;
    RInt             stop  = task->stop;

    RInt bytes = rho_linux_socket_tcp_read(self, pntr, start, stop);

    RSocketTcpEvent* result =
        rho_memory_arena_reserve_of(arena, RSocketTcpEvent, 1);

    if (result == NULL) return NULL;

    *result = rho_socket_tcp_event_read(
        (RSocketTcp*) self, pntr, start, stop, bytes, task->ctxt);

    return (RIoEvent*) result;
}

RBool32 rho_linux_socket_tcp_async_accept(RLinuxSocketTcp* self, RLinuxSocketTcp* value, RLinuxIoQueue* queue, void* ctxt)
{
    RLinuxSocketTcpAccept* result = rho_memory_pool_reserve_of(
        &queue->pool, RLinuxSocketTcpAccept, 1);

    if (result != NULL) {
        result->self      = self;
        result->value     = value;
        result->ctxt      = ctxt;
        result->callback  = rho_linux_socket_tcp_end_accept;
        result->list_next = NULL;

        if (rho_linux_socket_tcp_begin_accept(result, queue) != 0)
            return rho_linux_io_queue_submit(queue, (RLinuxIoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

RBool32 rho_linux_socket_tcp_async_connect(RLinuxSocketTcp* self, RHostIp host, RLinuxIoQueue* queue, void* ctxt)
{
    RLinuxSocketTcpConnect* result = rho_memory_pool_reserve_of(
        &queue->pool, RLinuxSocketTcpConnect, 1);

    if (result != NULL) {
        result->self      = self;
        result->host      = host;
        result->ctxt      = ctxt;
        result->callback  = rho_linux_socket_tcp_end_connect;
        result->list_next = NULL;

        if (rho_linux_socket_tcp_begin_connect(result, queue) != 0)
            return rho_linux_io_queue_submit(queue, (RLinuxIoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

RBool32 rho_linux_socket_tcp_async_write(RLinuxSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RLinuxIoQueue* queue, void* ctxt)
{
    RLinuxSocketTcpWrite* result = rho_memory_pool_reserve_of(
        &queue->pool, RLinuxSocketTcpWrite, 1);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->callback  = rho_linux_socket_tcp_end_write;
        result->list_next = NULL;

        if (rho_linux_socket_tcp_begin_write(result, queue) != 0)
            return rho_linux_io_queue_submit(queue, (RLinuxIoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

RBool32 rho_linux_socket_tcp_async_read(RLinuxSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RLinuxIoQueue* queue, void* ctxt)
{
    RLinuxSocketTcpRead* result = rho_memory_pool_reserve_of(
        &queue->pool, RLinuxSocketTcpRead, 1);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->callback  = rho_linux_socket_tcp_end_read;
        result->list_next = NULL;

        if (rho_linux_socket_tcp_begin_read(result, queue) != 0)
            return rho_linux_io_queue_submit(queue, (RLinuxIoTask*) result);

        rho_memory_pool_release(&queue->pool, result);
    }

    return 0;
}

#endif
