#ifndef PX_WIN32_ASYNC_NETWORK_SOCKET_TCP_C
#define PX_WIN32_ASYNC_NETWORK_SOCKET_TCP_C

#include "socket-tcp.h"

extern LPFN_CONNECTEX pxWin32ConnectEx;
extern LPFN_ACCEPTEX  pxWin32AcceptEx;

static b32
pxWin32AsyncBindSocketTcp(PxWin32Async* async, PxWin32SocketTcp* socket)
{
    HANDLE handle = ((HANDLE) socket->handle);

    if (CreateIoCompletionPort(handle, async->handle, 0, 0) == 0)
        return 0;

    return 1;
}

static b32
pxWin32SocketTcpTaskPrepare(PxWin32AsyncTask* task, PxWin32Async* async)
{
    PxWin32SocketTcpTask* self = ((PxWin32SocketTcpTask*) task->body);

    switch (self->kind) {
        case PxSocketTcpEvent_Accept: {
            PxWin32SocketTcpTaskAccept accept = self->accept;
            DWORD                      bytes  = 0;
            DWORD                      size   = sizeof (PxWin32SockAddrStorage);

            pxWin32AsyncBindSocketTcp(async, accept.listener);
            pxWin32AsyncBindSocketTcp(async, accept.socket);

            BOOL status = pxWin32AcceptEx(accept.listener->handle, accept.socket->handle,
                accept.buffer, 0, size, size, &bytes, &task->overlap);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case PxSocketTcpEvent_Connect: {
            PxWin32SocketTcpTaskConnect connect = self->connect;
            DWORD                       bytes   = 0;
            ssize                       length  = 0;

            PxWin32SockAddrStorage storage =
                pxWin32SockAddrStorageMake(connect.address, connect.port, &length);

            PxWin32SockAddr* sockaddr = (PxWin32SockAddr*) &storage;

            pxWin32AsyncBindSocketTcp(async, connect.socket);

            BOOL status = pxWin32ConnectEx(connect.socket->handle, sockaddr,
                length, 0, 0, &bytes, &task->overlap);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case PxSocketTcpEvent_Write: {
            PxWin32SocketTcpTaskWrite write = self->write;

            int status = WSASend(write.socket->handle, &write.wsabuf, 1,
                0, write.wsaflags, &task->overlap, 0);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case PxSocketTcpEvent_Read: {
            PxWin32SocketTcpTaskRead read = self->read;

            int status = WSARecv(read.socket->handle, &read.wsabuf, 1,
                0, &read.wsaflags, &task->overlap, 0);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        default: return 0;
    }

    return 1;
}

static b32
pxWin32SocketTcpTaskComplete(PxWin32AsyncTask* task, ssize bytes)
{
    PxWin32SocketTcpTask* self  = (PxWin32SocketTcpTask*) task->body;
    PxSocketTcpEvent*     event = (PxSocketTcpEvent*) task->event;

    switch (self->kind) {
        case PxSocketTcpEvent_Accept: {
            PxWin32SocketTcpTaskAccept accept  = self->accept;

            setsockopt(accept.socket->handle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
                ((char*) &accept.listener->handle), sizeof(accept.listener->handle));

            PxWin32SockAddrStorage storage = {0};
            INT                    length  = sizeof (PxWin32SockAddrStorage);

            PxWin32SockAddr* sockaddr = (PxWin32SockAddr*) &storage;

            getsockname(accept.socket->handle, sockaddr, &length);

            accept.socket->storage = storage;

            *event = pxSocketTcpEventAccept(accept.listener, accept.socket);
        } break;

        case PxSocketTcpEvent_Connect: {
            PxWin32SocketTcpTaskConnect connect = self->connect;
            DWORD                       bytes   = 0;
            DWORD                       flags   = 0;

            setsockopt(connect.socket->handle, SOL_SOCKET,
                SO_UPDATE_CONNECT_CONTEXT, 0, 0);

            BOOL status = WSAGetOverlappedResult(connect.socket->handle,
                &task->overlap, &bytes, 0, &flags);

            *event = pxSocketTcpEventConnect(connect.socket, status);
        } break;

        case PxSocketTcpEvent_Write: {
            PxWin32SocketTcpTaskWrite write = self->write;

            *event = pxSocketTcpEventWrite(write.socket, write.values,
                write.start, write.start + bytes);
        } break;

        case PxSocketTcpEvent_Read: {
            PxWin32SocketTcpTaskRead read = self->read;

            if (bytes > 0) {
                *event = pxSocketTcpEventRead(read.socket, read.values,
                    read.start, read.start + bytes);
            }
            else *event = pxSocketTcpEventClose(read.socket);
        } break;

        default: return 0;
    }

    return 1;
}

static PxWin32AsyncTask*
pxWin32SocketTcpTaskAccept(PxMemoryArena* arena, PxWin32SocketTcp* listener, PxWin32SocketTcp* socket)
{
    void* mark = pxMemoryArenaTell(arena);

    PxWin32AsyncTask*     result = pxMemoryArenaReserveOneOf(arena, PxWin32AsyncTask);
    PxWin32SocketTcpTask* body   = pxMemoryArenaReserveOneOf(arena, PxWin32SocketTcpTask);
    PxSocketTcpEvent*     event  = pxMemoryArenaReserveOneOf(arena, PxSocketTcpEvent);

    if (result != PX_NULL && body != PX_NULL && event != PX_NULL) {
        PxAddressIpKind kind    = pxWin32SocketTcpGetAddress(listener).kind;
        PxAddressIp     address = pxAddressIpEmpty(kind);

        if (pxWin32SocketTcpCreate(socket, address, 0) != 0) {
            result->kind          = 0;
            result->body          = body;
            result->event         = event;
            result->proc_prepare  = pxWin32SocketTcpTaskPrepare;
            result->proc_complete = pxWin32SocketTcpTaskComplete;
            result->pending_next  = PX_NULL;

            pxMemorySet(&result->overlap, sizeof result->overlap, 0x00);

            body->kind            = PxSocketTcpEvent_Accept;
            body->accept.listener = listener;
            body->accept.socket   = socket;

            return result;
        }
    }

    pxMemoryArenaRelease(arena, mark);

    return PX_NULL;
}

static PxWin32AsyncTask*
pxWin32SocketTcpTaskConnect(PxMemoryArena* arena, PxWin32SocketTcp* socket, PxAddressIp address, u16 port)
{
    void* mark = pxMemoryArenaTell(arena);

    PxWin32AsyncTask*     result = pxMemoryArenaReserveOneOf(arena, PxWin32AsyncTask);
    PxWin32SocketTcpTask* body   = pxMemoryArenaReserveOneOf(arena, PxWin32SocketTcpTask);
    PxSocketTcpEvent*     event  = pxMemoryArenaReserveOneOf(arena, PxSocketTcpEvent);

    if (result != PX_NULL && body != PX_NULL && event != PX_NULL) {
        if (pxWin32SocketTcpBind(socket) != 0) {
            result->kind          = 0;
            result->body          = body;
            result->event         = event;
            result->proc_prepare  = pxWin32SocketTcpTaskPrepare;
            result->proc_complete = pxWin32SocketTcpTaskComplete;
            result->pending_next  = PX_NULL;

            pxMemorySet(&result->overlap, sizeof result->overlap, 0x00);

            body->kind            = PxSocketTcpEvent_Connect;
            body->connect.socket  = socket;
            body->connect.address = address;
            body->connect.port    = port;

            return result;
        }
    }

    pxMemoryArenaRelease(arena, mark);

    return PX_NULL;
}

static PxWin32AsyncTask*
pxWin32SocketTcpTaskWrite(PxMemoryArena* arena, PxWin32SocketTcp* socket, u8* values, ssize start, ssize stop)
{
    void* mark = pxMemoryArenaTell(arena);

    PxWin32AsyncTask*     result = pxMemoryArenaReserveOneOf(arena, PxWin32AsyncTask);
    PxWin32SocketTcpTask* body   = pxMemoryArenaReserveOneOf(arena, PxWin32SocketTcpTask);
    PxSocketTcpEvent*     event  = pxMemoryArenaReserveOneOf(arena, PxSocketTcpEvent);

    if (result != PX_NULL && body != PX_NULL && event != PX_NULL) {
        result->kind          = 0;
        result->body          = body;
        result->event         = event;
        result->proc_prepare  = pxWin32SocketTcpTaskPrepare;
        result->proc_complete = pxWin32SocketTcpTaskComplete;
        result->pending_next  = PX_NULL;

        pxMemorySet(&result->overlap, sizeof result->overlap, 0x00);

        body->kind             = PxSocketTcpEvent_Write;
        body->write.socket     = socket;
        body->write.values     = values;
        body->write.start      = start;
        body->write.stop       = stop;
        body->write.wsabuf.buf = ((char*) values) + start;
        body->write.wsabuf.len = stop - start;
        body->write.wsaflags   = 0;

        return result;
    }

    pxMemoryArenaRelease(arena, mark);

    return PX_NULL;
}

static PxWin32AsyncTask*
pxWin32SocketTcpTaskRead(PxMemoryArena* arena, PxWin32SocketTcp* socket, u8* values, ssize start, ssize stop)
{
    void* mark = pxMemoryArenaTell(arena);

    PxWin32AsyncTask*     result = pxMemoryArenaReserveOneOf(arena, PxWin32AsyncTask);
    PxWin32SocketTcpTask* body   = pxMemoryArenaReserveOneOf(arena, PxWin32SocketTcpTask);
    PxSocketTcpEvent*     event  = pxMemoryArenaReserveOneOf(arena, PxSocketTcpEvent);

    if (result != PX_NULL && body != PX_NULL && event != PX_NULL) {
        result->kind          = 0;
        result->body          = body;
        result->event         = event;
        result->proc_prepare  = pxWin32SocketTcpTaskPrepare;
        result->proc_complete = pxWin32SocketTcpTaskComplete;
        result->pending_next  = PX_NULL;

        pxMemorySet(&result->overlap, sizeof result->overlap, 0x00);

        body->kind            = PxSocketTcpEvent_Read;
        body->read.socket     = socket;
        body->read.values     = values;
        body->read.start      = start;
        body->read.stop       = stop;
        body->read.wsabuf.buf = ((char*) values) + start;
        body->read.wsabuf.len = stop - start;
        body->read.wsaflags   = 0;

        return result;
    }

    pxMemoryArenaRelease(arena, mark);

    return PX_NULL;
}

b32
pxWin32SocketTcpAcceptAsync(PxAsync* async, PxMemoryArena* arena, ssize kind, PxWin32SocketTcp* self, PxWin32SocketTcp* value)
{
    return pxAsyncSubmit(async, kind, pxWin32SocketTcpTaskAccept(arena, self, value));
}

b32
pxWin32SocketTcpConnectAsync(PxAsync* async, PxMemoryArena* arena, ssize kind, PxWin32SocketTcp* self, PxAddressIp address, u16 port)
{
    return pxAsyncSubmit(async, kind, pxWin32SocketTcpTaskConnect(arena, self, address, port));
}

b32
pxWin32SocketTcpWriteAsync(PxAsync* async, PxMemoryArena* arena, ssize kind, PxWin32SocketTcp* self, u8* values, ssize start, ssize stop)
{
    return pxAsyncSubmit(async, kind, pxWin32SocketTcpTaskWrite(arena, self, values, start, stop));
}

b32
pxWin32SocketTcpReadAsync(PxAsync* async, PxMemoryArena* arena, ssize kind, PxWin32SocketTcp* self, u8* values, ssize start, ssize stop)
{
    return pxAsyncSubmit(async, kind, pxWin32SocketTcpTaskRead(arena, self, values, start, stop));
}

#endif // PX_WIN32_ASYNC_NETWORK_SOCKET_TCP_C
