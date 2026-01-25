#ifndef P_SYSTEM_LINUX_NETWORK_ASYNC_SOCKET_TCP_C
#define P_SYSTEM_LINUX_NETWORK_ASYNC_SOCKET_TCP_C

#include "socket-tcp.h"

static B32 pLinuxAsyncIoQueueBindSocketTcp(PLinuxAsyncIoQueue* self, PLinuxSocketTcp* socket, PLinuxAsyncIoTask* task)
{
    int handle = (int) socket->handle;
    int queue  = (int) self->handle;

    PEpollEvent notif;

    notif.events   = EPOLLIN | EPOLLOUT;
    notif.data.ptr = task;

    int status = epoll_ctl(queue, EPOLL_CTL_ADD, handle, &notif);

    if (status == -1 && errno == EEXIST)
        status = epoll_ctl(queue, EPOLL_CTL_MOD, handle, &notif);

    return status != -1 ? 1 : 0;
}

static B32 pLinuxSocketTcpAcceptBegin(PLinuxSocketTcpAccept* task, PLinuxAsyncIoQueue* queue)
{
    PLinuxSocketTcp* self  = task->self;
    PLinuxSocketTcp* value = task->value;

    pLinuxAsyncIoQueueBindSocketTcp(queue,
        self, (PLinuxAsyncIoTask*) task);

    return 1;
}

static PAsyncIoEventKind pLinuxSocketTcpAcceptEnd(PLinuxSocketTcpAccept* task, PMemoryArena* arena, PAsyncIoEvent** event)
{
    PLinuxSocketTcp* self  = task->self;
    PLinuxSocketTcp* value = task->value;

    B32 status = pLinuxSocketTcpAccept(self, value);

    if (status == 0) return PAsyncIoEvent_None;

    PSocketTcpEvent* result =
        pMemoryArenaReserveOneOf(arena, PSocketTcpEvent);

    if (result != NULL) {
        *result = pSocketTcpEventAccept((PSocketTcp*) self,
            (PSocketTcp*) value, task->ctxt);

        if (event != NULL) *event = (PAsyncIoEvent*) result;

        return PAsyncIoEvent_Tcp;
    }

    return PAsyncIoEvent_None;
}

static B32 pLinuxSocketTcpConnectBegin(PLinuxSocketTcpConnect* task, PLinuxAsyncIoQueue* queue)
{
    PLinuxSocketTcp* self = task->self;
    PHostIp          host = task->host;

    pLinuxAsyncIoQueueBindSocketTcp(queue,
        self, (PLinuxAsyncIoTask*) task);

    return 1;
}

static PAsyncIoEventKind pLinuxSocketTcpConnectEnd(PLinuxSocketTcpConnect* task, PMemoryArena* arena, PAsyncIoEvent** event)
{
    PLinuxSocketTcp* self = task->self;
    PHostIp          host = task->host;

    B32 status = pLinuxSocketTcpConnect(self, host);

    PSocketTcpEvent* result =
        pMemoryArenaReserveOneOf(arena, PSocketTcpEvent);

    if (result != NULL) {
        *result = pSocketTcpEventConnect((PSocketTcp*) self,
            host, status != 0 ? 1 : 0, task->ctxt);

        if (event != NULL) *event = (PAsyncIoEvent*) result;

        return PAsyncIoEvent_Tcp;
    }

    return PAsyncIoEvent_None;
}

static B32 pLinuxSocketTcpWriteBegin(PLinuxSocketTcpWrite* task, PLinuxAsyncIoQueue* queue)
{
    PLinuxSocketTcp* self = task->self;

    pLinuxAsyncIoQueueBindSocketTcp(queue,
        self, (PLinuxAsyncIoTask*) task);

    return 1;
}

static PAsyncIoEventKind pLinuxSocketTcpWriteEnd(PLinuxSocketTcpWrite* task, PMemoryArena* arena, PAsyncIoEvent** event)
{
    PLinuxSocketTcp* self  = task->self;
    U8*              pntr  = task->pntr;
    Int              start = task->start;
    Int              stop  = task->stop;

    Int bytes = pLinuxSocketTcpWrite(self, pntr, start, stop);

    PSocketTcpEvent* result =
        pMemoryArenaReserveOneOf(arena, PSocketTcpEvent);

    if (result != NULL) {
        *result = pSocketTcpEventWrite((PSocketTcp*) self,
            pntr, start, stop, bytes, task->ctxt);

        if (event != NULL) *event = (PAsyncIoEvent*) result;

        return PAsyncIoEvent_Tcp;
    }

    return PAsyncIoEvent_None;
}

static B32 pLinuxSocketTcpReadBegin(PLinuxSocketTcpRead* task, PLinuxAsyncIoQueue* queue)
{
    PLinuxSocketTcp* self = task->self;

    pLinuxAsyncIoQueueBindSocketTcp(queue,
        self, (PLinuxAsyncIoTask*) task);

    return 1;
}

static PAsyncIoEventKind pLinuxSocketTcpReadEnd(PLinuxSocketTcpRead* task, PMemoryArena* arena, PAsyncIoEvent** event)
{
    PLinuxSocketTcp* self  = task->self;
    U8*              pntr  = task->pntr;
    Int              start = task->start;
    Int              stop  = task->stop;

    Int bytes = pLinuxSocketTcpRead(self, pntr, start, stop);

    PSocketTcpEvent* result =
        pMemoryArenaReserveOneOf(arena, PSocketTcpEvent);

    if (result != NULL) {
        *result = pSocketTcpEventRead((PSocketTcp*) self,
            pntr, start, stop, bytes, task->ctxt);

        if (event != NULL) *event = (PAsyncIoEvent*) result;

        return PAsyncIoEvent_Tcp;
    }

    return PAsyncIoEvent_None;
}

B32 pLinuxSocketTcpAcceptAsync(PLinuxSocketTcp* self, PLinuxSocketTcp* value, PLinuxAsyncIoQueue* queue, void* ctxt)
{
    PLinuxSocketTcpAccept* result =
        pMemoryPoolReserveOneOf(&queue->pool, PLinuxSocketTcpAccept);

    if (result != NULL) {
        result->self      = self;
        result->value     = value;
        result->ctxt      = ctxt;
        result->callback  = pLinuxSocketTcpAcceptEnd;
        result->list_next = NULL;

        if (pLinuxSocketTcpAcceptBegin(result, queue) != 0)
            return pLinuxAsyncIoQueueSubmit(queue, (PLinuxAsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

B32 pLinuxSocketTcpConnectAsync(PLinuxSocketTcp* self, PHostIp host, PLinuxAsyncIoQueue* queue, void* ctxt)
{
    PLinuxSocketTcpConnect* result =
        pMemoryPoolReserveOneOf(&queue->pool, PLinuxSocketTcpConnect);

    if (result != NULL) {
        result->self      = self;
        result->host      = host;
        result->ctxt      = ctxt;
        result->callback  = pLinuxSocketTcpConnectEnd;
        result->list_next = NULL;

        if (pLinuxSocketTcpConnectBegin(result, queue) != 0)
            return pLinuxAsyncIoQueueSubmit(queue, (PLinuxAsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

B32 pLinuxSocketTcpWriteAsync(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop, PLinuxAsyncIoQueue* queue, void* ctxt)
{
    PLinuxSocketTcpWrite* result =
        pMemoryPoolReserveOneOf(&queue->pool, PLinuxSocketTcpWrite);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->callback  = pLinuxSocketTcpWriteEnd;
        result->list_next = NULL;

        if (pLinuxSocketTcpWriteBegin(result, queue) != 0)
            return pLinuxAsyncIoQueueSubmit(queue, (PLinuxAsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

B32 pLinuxSocketTcpReadAsync(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop, PLinuxAsyncIoQueue* queue, void* ctxt)
{
    PLinuxSocketTcpRead* result =
        pMemoryPoolReserveOneOf(&queue->pool, PLinuxSocketTcpRead);

    if (result != NULL) {
        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->ctxt      = ctxt;
        result->callback  = pLinuxSocketTcpReadEnd;
        result->list_next = NULL;

        if (pLinuxSocketTcpReadBegin(result, queue) != 0)
            return pLinuxAsyncIoQueueSubmit(queue, (PLinuxAsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

#endif
