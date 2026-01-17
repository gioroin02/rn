#ifndef P_SYSTEM_WIN32_NETWORK_ASYNC_SOCKET_TCP_C
#define P_SYSTEM_WIN32_NETWORK_ASYNC_SOCKET_TCP_C

#include "socket-tcp.h"

extern LPFN_CONNECTEX WSAConnectEx;
extern LPFN_ACCEPTEX  WSAAcceptEx;

static Bool pWin32AsyncIoQueueBindSocketTcp(PWin32AsyncIoQueue* self, PWin32SocketTcp* socket)
{
    HANDLE handle = ((HANDLE) socket->handle);
    HANDLE result = CreateIoCompletionPort(handle, self->handle, 0, 0);

    return result != NULL ? 1 : 0;
}

static Bool pWin32SocketTcpAcceptBegin(PWin32SocketTcpAccept* task, PWin32AsyncIoQueue* queue)
{
    PWin32SocketTcp* self   = task->self;
    PWin32SocketTcp* value  = task->value;
    U8*              buffer = task->buff;
    Int              size   = sizeof task->buff / 2;

    if (pWin32AsyncIoQueueBindSocketTcp(queue, value) == 0) return 0;

    pWin32AsyncIoQueueBindSocketTcp(queue, self);

    BOOL status = WSAAcceptEx(self->handle, value->handle,
        buffer, 0, size, size, NULL, &task->overlap);

    if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static void pWin32SocketTcpAcceptEnd(PWin32SocketTcpAccept* task, Int bytes)
{
    PWin32SocketTcp* self  = task->self;
    PWin32SocketTcp* value = task->value;

    setsockopt(value->handle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
        (I8*) &self->handle, sizeof self->handle);

    PWin32AddrStorage storage;
    PWin32Addr*       sockaddr = (PWin32Addr*) &storage;
    Int               length   = sizeof storage;

    getsockname(value->handle, sockaddr, (int*) &length);

    value->storage = storage;

    if (task->pntr_proc != NULL) {
        ((PSocketTcpAcceptProc*) task->pntr_proc)(task->pntr_ctxt,
            (PSocketTcp*) self, (PSocketTcp*) value);
    }
}

static Bool pWin32SocketTcpConnectBegin(PWin32SocketTcpConnect* task, PWin32AsyncIoQueue* queue)
{
    PWin32SocketTcp* self = task->self;
    PHostIp          host = task->host;

    pWin32AsyncIoQueueBindSocketTcp(queue, self);

    PWin32AddrStorage storage;
    PWin32Addr*       sockaddr = (PWin32Addr*) &storage;
    Int               length   = 0;

    storage = pWin32AddrStorageMake(host.address, host.port, &length);

    BOOL status = WSAConnectEx(self->handle, sockaddr,
        length, 0, 0, NULL, &task->overlap);

    if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static void pWin32SocketTcpConnectEnd(PWin32SocketTcpConnect* task, Int bytes)
{
    PWin32SocketTcp* self = task->self;
    PHostIp          host = task->host;

    // Note: This is useless but must not be null.
    Int flag = 0;

    setsockopt(self->handle, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);

    BOOL status = WSAGetOverlappedResult(self->handle,
        &task->overlap, (DWORD*) &bytes, 0, (DWORD*) &flag);

    if (task->pntr_proc != NULL) {
        ((PSocketTcpConnectProc*) task->pntr_proc)(task->pntr_ctxt,
            (PSocketTcp*) self, host, status != 0 ? 1 : 0);
    }
}

static Bool pWin32SocketTcpWriteBegin(PWin32SocketTcpWrite* task, PWin32AsyncIoQueue* queue)
{
    PWin32SocketTcp* self   = task->self;
    I8*              pntr   = ((I8*) task->pntr) + task->start;
    Int              size   = task->stop - task->start;
    WSABUF*          buffer = &task->buffer;

    pWin32AsyncIoQueueBindSocketTcp(queue, self);

    buffer->buf = pntr;
    buffer->len = size;

    int status = WSASend(self->handle, buffer, 1, NULL, 0, &task->overlap, NULL);

    if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static void pWin32SocketTcpWriteEnd(PWin32SocketTcpWrite* task, Int bytes)
{
    PWin32SocketTcp* self  = task->self;
    U8*              pntr  = task->pntr;
    Int              start = task->start;
    Int              stop  = task->stop;

    if (task->pntr_proc != NULL) {
        ((PSocketTcpWriteProc*) task->pntr_proc)(task->pntr_ctxt,
            (PSocketTcp*) self, pntr, start, stop, bytes);
    }
}

static Bool pWin32SocketTcpReadBegin(PWin32SocketTcpRead* task, PWin32AsyncIoQueue* queue)
{
    PWin32SocketTcp* self   = task->self;
    I8*              pntr   = ((I8*) task->pntr) + task->start;
    Int              size   = task->stop - task->start;
    WSABUF*          buffer = &task->buffer;

    // Note: This parameter is useless but must not be null.
    Int flag = 0;

    pWin32AsyncIoQueueBindSocketTcp(queue, self);

    buffer->buf = pntr;
    buffer->len = size;

    int status = WSARecv(self->handle, buffer, 1,
        NULL, (DWORD*) &flag, &task->overlap, NULL);

    if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        return 0;

    return 1;
}

static void pWin32SocketTcpReadEnd(PWin32SocketTcpRead* task, Int bytes)
{
    PWin32SocketTcp* self  = task->self;
    U8*              pntr  = task->pntr;
    Int              start = task->start;
    Int              stop  = task->stop;

    if (task->pntr_proc != NULL) {
        ((PSocketTcpReadProc*) task->pntr_proc)(task->pntr_ctxt,
            (PSocketTcp*) self, pntr, start, stop, bytes);
    }
}

Bool pWin32SocketTcpAcceptAsync(PWin32SocketTcp* self, PWin32SocketTcp* value, PWin32AsyncIoQueue* queue, void* ctxt, void* proc)
{
    PHostIp host = pWin32SocketTcpGetHost(self);

    if (pWin32SocketTcpCreate(value, host) == 0) return 0;

    PWin32SocketTcpAccept* result =
        pMemoryPoolReserveOneOf(&queue->pool, PWin32SocketTcpAccept);

    if (result != NULL) {
        pMemorySet(&result->overlap, sizeof result->overlap, 0x00);
        pMemorySet(result->buff,     sizeof result->buff,    0x00);

        result->self      = self;
        result->value     = value;
        result->pntr_ctxt = ctxt;
        result->pntr_proc = proc;
        result->callback  = pWin32SocketTcpAcceptEnd;
        result->list_next = NULL;

        if (pWin32SocketTcpAcceptBegin(result, queue) != 0)
            return pWin32AsyncIoQueueSubmit(queue, (PWin32AsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

Bool pWin32SocketTcpConnectAsync(PWin32SocketTcp* self, PHostIp host, PWin32AsyncIoQueue* queue, void* ctxt, void* proc)
{
    if (pWin32SocketTcpBind(self) == 0) return 0;

    PWin32SocketTcpConnect* result =
        pMemoryPoolReserveOneOf(&queue->pool, PWin32SocketTcpConnect);

    if (result != NULL) {
        pMemorySet(&result->overlap, sizeof result->overlap, 0x00);

        result->self      = self;
        result->host      = host;
        result->pntr_ctxt = ctxt;
        result->pntr_proc = proc;
        result->callback  = pWin32SocketTcpConnectEnd;
        result->list_next = NULL;

        if (pWin32SocketTcpConnectBegin(result, queue) != 0)
            return pWin32AsyncIoQueueSubmit(queue, (PWin32AsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

Bool pWin32SocketTcpWriteAsync(PWin32SocketTcp* self, U8* pntr, Int start, Int stop, PWin32AsyncIoQueue* queue, void* ctxt, void* proc)
{
    PWin32SocketTcpWrite* result =
        pMemoryPoolReserveOneOf(&queue->pool, PWin32SocketTcpWrite);

    if (result != NULL) {
        pMemorySet(&result->overlap, sizeof result->overlap, 0x00);

        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->pntr_ctxt = ctxt;
        result->pntr_proc = proc;
        result->callback  = pWin32SocketTcpWriteEnd;
        result->list_next = NULL;

        if (pWin32SocketTcpWriteBegin(result, queue) != 0)
            return pWin32AsyncIoQueueSubmit(queue, (PWin32AsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

Bool pWin32SocketTcpReadAsync(PWin32SocketTcp* self, U8* pntr, Int start, Int stop, PWin32AsyncIoQueue* queue, void* ctxt, void* proc)
{
    PWin32SocketTcpRead* result =
        pMemoryPoolReserveOneOf(&queue->pool, PWin32SocketTcpRead);

    if (result != NULL) {
        pMemorySet(&result->overlap, sizeof result->overlap, 0x00);

        result->self      = self;
        result->pntr      = pntr;
        result->start     = start;
        result->stop      = stop;
        result->pntr_ctxt = ctxt;
        result->pntr_proc = proc;
        result->callback  = pWin32SocketTcpReadEnd;
        result->list_next = NULL;

        if (pWin32SocketTcpReadBegin(result, queue) != 0)
            return pWin32AsyncIoQueueSubmit(queue, (PWin32AsyncIoTask*) result);

        pMemoryPoolRelease(&queue->pool, result);
    }

    return 0;
}

#endif // P_SYSTEM_WIN32_NETWORK_ASYNC_SOCKET_TCP_C
