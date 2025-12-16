#ifndef PX_WIN32_NETWORK_ASYNC_C
#define PX_WIN32_NETWORK_ASYNC_C

#include "async.h"

static b32
pxWin32SocketTCPBindToAsyncIOQueue(PxWin32SocketTCP* self, PxWin32AsyncIOQueue* queue)
{
    if (self == 0 || queue == 0 || self->storage.ss_family == 0)
        return 0;

    HANDLE handle = ((HANDLE) self->handle);

    if (CreateIoCompletionPort(handle, queue->handle, 0, 0) == 0)
        return 0;

    return 1;
}

static void
pxWin32SocketTCPAsyncCallback(PxWin32AsyncIOTask* task, PxSocketTCPEvent event)
{
    if (task->procCallback != 0)
        ((PxWin32AsyncIOProcCallback*) task->procCallback)(event.ctxt, &event);
}

static b32
pxWin32SocketTCPAsyncPrepare(PxWin32AsyncIOTask* task, PxWin32AsyncIOQueue* queue)
{
    PxWin32SocketTCPTask* self = ((PxWin32SocketTCPTask*) task->ctxt);

    switch (self->kind) {
        case PxSocketTCPAsync_Accept: {
            PxWin32SocketTCPTaskAccept accept = self->accept;

            pxWin32SocketTCPBindToAsyncIOQueue(accept.listener, queue);

            if (pxWin32SocketTCPBindToAsyncIOQueue(accept.socket, queue) == 0)
                return 0;

            DWORD bytes = 0;

            BOOL status = acceptEx(accept.listener->handle, accept.socket->handle,
                accept.buffer, 0, accept.size, accept.size, &bytes, &task->overlap);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case PxSocketTCPAsync_Connect: {
            PxWin32SocketTCPTaskConnect connect = self->connect;

            pxWin32SocketTCPBindToAsyncIOQueue(connect.socket, queue);

            DWORD bytes = 0;
            ssize type  = 0;

            PxSockAddrStorage storage = pxSockAddrStorageMake(connect.address, connect.port, &type);

            BOOL status = connectEx(connect.socket->handle,
                ((PxSockAddr*) &storage), type, 0, 0, &bytes, &task->overlap);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case PxSocketTCPAsync_Write: {
            PxWin32SocketTCPTaskWrite write = self->write;

            int status = WSASend(write.socket->handle, &write.buffer, 1,
                0, write.flags, &task->overlap, 0);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case PxSocketTCPAsync_Read: {
            PxWin32SocketTCPTaskRead read = self->read;

            int status = WSARecv(read.socket->handle, &read.buffer, 1,
                0, &read.flags, &task->overlap, 0);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        default: return 0;
    }

    return 1;
}

static b32
pxWin32SocketTCPAsyncComplete(PxWin32AsyncIOTask* task, ssize bytes)
{
    PxWin32SocketTCPTask* self  = ((PxWin32SocketTCPTask*) task->ctxt);
    PxSocketTCPEvent      event = {0};

    switch (self->kind) {
        case PxSocketTCPAsync_Accept: {
            PxWin32SocketTCPTaskAccept accept = self->accept;

            setsockopt(accept.socket->handle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
                ((char*) &accept.listener->handle), sizeof(accept.listener->handle));

            PxSockAddrStorage storage = {0};
            INT               size    = accept.size;

            getsockname(accept.socket->handle, ((PxSockAddr*) &storage), &size);

            accept.socket->storage = storage;

            event = pxSocketTCPEventAccept(self->ctxt, accept.listener, accept.socket);
        } break;

        case PxSocketTCPAsync_Connect: {
            PxWin32SocketTCPTaskConnect connect = self->connect;

            setsockopt(connect.socket->handle,
                SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, 0, 0);

            DWORD bytes = 0;
            DWORD flags = 0;

            BOOL status = WSAGetOverlappedResult(
                connect.socket->handle, &task->overlap, &bytes, 0, &flags);

            event = pxSocketTCPEventConnect(self->ctxt, connect.socket, status);
        } break;

        case PxSocketTCPAsync_Write: {
            PxWin32SocketTCPTaskWrite write = self->write;

            event = pxSocketTCPEventWrite(self->ctxt, write.socket,
                write.values, write.start, write.start + bytes);
        } break;

        case PxSocketTCPAsync_Read: {
            PxWin32SocketTCPTaskRead read = self->read;

            if (bytes > 0) {
                event = pxSocketTCPEventRead(self->ctxt, read.socket,
                    read.values, read.start, read.start + bytes);
            } else
                event = pxSocketTCPEventClose(task->ctxt, read.socket);
        } break;

        default: return 0;
    }

    pxWin32SocketTCPAsyncCallback(task, event);

    return 1;
}

PxWin32AsyncIOTask*
pxWin32SocketTCPAsyncAccept(PxMemoryArena* arena, void* ctxt, void* proc,
    PxWin32SocketTCP* listener, PxWin32SocketTCP* socket)
{
    PxWin32AsyncIOTask* result =
        pxMemoryArenaReserveOneOf(arena, PxWin32AsyncIOTask);

    PxWin32SocketTCPTask* body =
        pxMemoryArenaReserveOneOf(arena, PxWin32SocketTCPTask);

    if (result != 0 && body != 0) {
        PxAddressIP address = pxAddressIPEmpty(
            pxWin32SocketTCPGetAddress(listener).kind);

        if (pxWin32SocketTCPCreate(socket, address, 0) != 0) {
            *result = (PxWin32AsyncIOTask) {
                .ctxt         = body,
                .procCallback = proc,
                .procPrepare  = &pxWin32SocketTCPAsyncPrepare,
                .procComplete = &pxWin32SocketTCPAsyncComplete,
            };

            *body = (PxWin32SocketTCPTask) {
                .kind = PxSocketTCPAsync_Accept,
                .ctxt = ctxt,

                .accept = {
                    .listener = listener,
                    .socket   = socket,
                    .size     = 256,
                },
            };

            return result;
        }
    }

    pxMemoryArenaRelease(arena, result);

    return 0;
}

PxWin32AsyncIOTask*
pxWin32SocketTCPAsyncConnect(PxMemoryArena* arena, void* ctxt, void* proc,
    PxWin32SocketTCP* socket, PxAddressIP address, u16 port)
{
    PxWin32AsyncIOTask* result =
        pxMemoryArenaReserveOneOf(arena, PxWin32AsyncIOTask);

    PxWin32SocketTCPTask* body =
        pxMemoryArenaReserveOneOf(arena, PxWin32SocketTCPTask);

    if (result != 0 && body != 0) {
        if (pxWin32SocketTCPBind(socket) != 0) {
            *result = (PxWin32AsyncIOTask) {
                .ctxt         = body,
                .procCallback = proc,
                .procPrepare  = &pxWin32SocketTCPAsyncPrepare,
                .procComplete = &pxWin32SocketTCPAsyncComplete,
            };

            *body = (PxWin32SocketTCPTask) {
                .kind = PxSocketTCPAsync_Connect,
                .ctxt = ctxt,

                .connect = {
                    .socket  = socket,
                    .address = address,
                    .port    = port,
                },
            };

            return result;
        }
    }

    pxMemoryArenaRelease(arena, result);

    return 0;
}

PxWin32AsyncIOTask*
pxWin32SocketTCPAsyncWrite(PxMemoryArena* arena, void* ctxt, void* proc,
    PxWin32SocketTCP* socket, u8* values, ssize start, ssize stop)
{
    PxWin32AsyncIOTask* result =
        pxMemoryArenaReserveOneOf(arena, PxWin32AsyncIOTask);

    PxWin32SocketTCPTask* body =
        pxMemoryArenaReserveOneOf(arena, PxWin32SocketTCPTask);

    if (result != 0) {
        *result = (PxWin32AsyncIOTask) {
            .ctxt         = body,
            .procCallback = proc,
            .procPrepare  = &pxWin32SocketTCPAsyncPrepare,
            .procComplete = &pxWin32SocketTCPAsyncComplete,
        };

        *body = (PxWin32SocketTCPTask) {
            .kind = PxSocketTCPAsync_Write,
            .ctxt = ctxt,

            .write = {
                .socket = socket,
                .values = values,
                .start  = start,
                .stop   = stop,
                .buffer = (WSABUF) {
                    .buf = ((char*) values) + start,
                    .len = stop - start,
                },
            },
        };

        return result;
    }

    pxMemoryArenaRelease(arena, result);

    return 0;
}

PxWin32AsyncIOTask*
pxWin32SocketTCPAsyncRead(PxMemoryArena* arena, void* ctxt, void* proc,
    PxWin32SocketTCP* socket, u8* values, ssize start, ssize stop)
{
    PxWin32AsyncIOTask* result =
        pxMemoryArenaReserveOneOf(arena, PxWin32AsyncIOTask);

    PxWin32SocketTCPTask* body =
        pxMemoryArenaReserveOneOf(arena, PxWin32SocketTCPTask);

    if (result != 0) {
        *result = (PxWin32AsyncIOTask) {
            .ctxt         = body,
            .procCallback = proc,
            .procPrepare  = &pxWin32SocketTCPAsyncPrepare,
            .procComplete = &pxWin32SocketTCPAsyncComplete,
        };

        *body = (PxWin32SocketTCPTask) {
            .kind = PxSocketTCPAsync_Read,
            .ctxt = ctxt,

            .write = {
                .socket = socket,
                .values = values,
                .start  = start,
                .stop   = stop,
                .buffer = (WSABUF) {
                    .buf = ((char*) values) + start,
                    .len = stop - start,
                },
            },
        };

        return result;
    }

    pxMemoryArenaRelease(arena, result);

    return 0;
}

#endif // PX_WIN32_NETWORK_ASYNC_C
