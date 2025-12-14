#ifndef RN_WIN32_NETWORK_ASYNC_C
#define RN_WIN32_NETWORK_ASYNC_C

#include "./async.h"

static b32
rnWin32SocketTCPBindToAsyncIOQueue(RnWin32SocketTCP* self, RnWin32AsyncIOQueue* queue)
{
    if (self == 0 || queue == 0 || self->storage.ss_family == 0)
        return 0;

    HANDLE handle = ((HANDLE) self->handle);

    if (CreateIoCompletionPort(handle, queue->handle, 0, 0) == 0)
        return 0;

    return 1;
}

static void
rnWin32SocketTCPAsyncCallback(RnWin32AsyncIOTask* task, RnSocketTCPEvent event)
{
    if (task->procCallback != 0)
        ((RnWin32AsyncIOProcCallback*) task->procCallback)(event.ctxt, &event);
}

static b32
rnWin32SocketTCPAsyncPrepare(RnWin32AsyncIOTask* task, RnWin32AsyncIOQueue* queue)
{
    RnWin32SocketTCPTask* self = ((RnWin32SocketTCPTask*) task->ctxt);

    switch (self->kind) {
        case RnSocketTCPAsync_Accept: {
            RnWin32SocketTCPTaskAccept accept = self->accept;

            rnWin32SocketTCPBindToAsyncIOQueue(accept.listener, queue);

            if (rnWin32SocketTCPBindToAsyncIOQueue(accept.socket, queue) == 0)
                return 0;

            DWORD bytes = 0;

            BOOL status = acceptEx(accept.listener->handle, accept.socket->handle,
                accept.buffer, 0, accept.size, accept.size, &bytes, &task->overlap);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case RnSocketTCPAsync_Connect: {
            RnWin32SocketTCPTaskConnect connect = self->connect;

            rnWin32SocketTCPBindToAsyncIOQueue(connect.socket, queue);

            DWORD bytes = 0;
            ssize type  = 0;

            RnSockAddrStorage storage = rnSockAddrStorageMake(connect.address, connect.port, &type);

            BOOL status = connectEx(connect.socket->handle,
                ((RnSockAddr*) &storage), type, 0, 0, &bytes, &task->overlap);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case RnSocketTCPAsync_Write: {
            RnWin32SocketTCPTaskWrite write = self->write;

            int status = WSASend(write.socket->handle, &write.buffer, 1,
                0, write.flags, &task->overlap, 0);

            if (status == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
                return 0;
        } break;

        case RnSocketTCPAsync_Read: {
            RnWin32SocketTCPTaskRead read = self->read;

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
rnWin32SocketTCPAsyncComplete(RnWin32AsyncIOTask* task, ssize bytes)
{
    RnWin32SocketTCPTask* self  = ((RnWin32SocketTCPTask*) task->ctxt);
    RnSocketTCPEvent      event = {0};

    switch (self->kind) {
        case RnSocketTCPAsync_Accept: {
            RnWin32SocketTCPTaskAccept accept = self->accept;

            setsockopt(accept.socket->handle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
                ((char*) &accept.listener->handle), sizeof(accept.listener->handle));

            RnSockAddrStorage storage = {0};
            INT               size    = accept.size;

            getsockname(accept.socket->handle, ((RnSockAddr*) &storage), &size);

            accept.socket->storage = storage;

            event = rnSocketTCPEventAccept(self->ctxt, accept.listener, accept.socket);
        } break;

        case RnSocketTCPAsync_Connect: {
            RnWin32SocketTCPTaskConnect connect = self->connect;

            setsockopt(connect.socket->handle,
                SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, 0, 0);

            DWORD bytes = 0;
            DWORD flags = 0;

            BOOL status = WSAGetOverlappedResult(
                connect.socket->handle, &task->overlap, &bytes, 0, &flags);

            event = rnSocketTCPEventConnect(self->ctxt, connect.socket, status);
        } break;

        case RnSocketTCPAsync_Write: {
            RnWin32SocketTCPTaskWrite write = self->write;

            event = rnSocketTCPEventWrite(self->ctxt, write.socket,
                write.values, write.start, write.start + bytes);
        } break;

        case RnSocketTCPAsync_Read: {
            RnWin32SocketTCPTaskRead read = self->read;

            if (bytes > 0) {
                event = rnSocketTCPEventRead(self->ctxt, read.socket,
                    read.values, read.start, read.start + bytes);
            } else
                event = rnSocketTCPEventClose(task->ctxt, read.socket);
        } break;

        default: return 0;
    }

    rnWin32SocketTCPAsyncCallback(task, event);

    return 1;
}

RnWin32AsyncIOTask*
rnWin32SocketTCPAsyncAccept(RnMemoryArena* arena, void* ctxt, void* proc,
    RnWin32SocketTCP* listener, RnWin32SocketTCP* socket)
{
    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    RnWin32SocketTCPTask* body =
        rnMemoryArenaReserveOneOf(arena, RnWin32SocketTCPTask);

    if (result != 0 && body != 0) {
        RnAddressIP address = rnAddressIPEmpty(
            rnWin32SocketTCPGetAddress(listener).kind);

        if (rnWin32SocketTCPCreate(socket, address, 0) != 0) {
            *result = (RnWin32AsyncIOTask) {
                .ctxt         = body,
                .procCallback = proc,
                .procPrepare  = &rnWin32SocketTCPAsyncPrepare,
                .procComplete = &rnWin32SocketTCPAsyncComplete,
            };

            *body = (RnWin32SocketTCPTask) {
                .kind = RnSocketTCPAsync_Accept,
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

    rnMemoryArenaRelease(arena, result);

    return 0;
}

RnWin32AsyncIOTask*
rnWin32SocketTCPAsyncConnect(RnMemoryArena* arena, void* ctxt, void* proc,
    RnWin32SocketTCP* socket, RnAddressIP address, u16 port)
{
    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    RnWin32SocketTCPTask* body =
        rnMemoryArenaReserveOneOf(arena, RnWin32SocketTCPTask);

    if (result != 0 && body != 0) {
        if (rnWin32SocketTCPBind(socket) != 0) {
            *result = (RnWin32AsyncIOTask) {
                .ctxt         = body,
                .procCallback = proc,
                .procPrepare  = &rnWin32SocketTCPAsyncPrepare,
                .procComplete = &rnWin32SocketTCPAsyncComplete,
            };

            *body = (RnWin32SocketTCPTask) {
                .kind = RnSocketTCPAsync_Connect,
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

    rnMemoryArenaRelease(arena, result);

    return 0;
}

RnWin32AsyncIOTask*
rnWin32SocketTCPAsyncWrite(RnMemoryArena* arena, void* ctxt, void* proc,
    RnWin32SocketTCP* socket, u8* values, ssize start, ssize stop)
{
    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    RnWin32SocketTCPTask* body =
        rnMemoryArenaReserveOneOf(arena, RnWin32SocketTCPTask);

    if (result != 0) {
        *result = (RnWin32AsyncIOTask) {
            .ctxt         = body,
            .procCallback = proc,
            .procPrepare  = &rnWin32SocketTCPAsyncPrepare,
            .procComplete = &rnWin32SocketTCPAsyncComplete,
        };

        *body = (RnWin32SocketTCPTask) {
            .kind = RnSocketTCPAsync_Write,
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

    rnMemoryArenaRelease(arena, result);

    return 0;
}

RnWin32AsyncIOTask*
rnWin32SocketTCPAsyncRead(RnMemoryArena* arena, void* ctxt, void* proc,
    RnWin32SocketTCP* socket, u8* values, ssize start, ssize stop)
{
    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    RnWin32SocketTCPTask* body =
        rnMemoryArenaReserveOneOf(arena, RnWin32SocketTCPTask);

    if (result != 0) {
        *result = (RnWin32AsyncIOTask) {
            .ctxt         = body,
            .procCallback = proc,
            .procPrepare  = &rnWin32SocketTCPAsyncPrepare,
            .procComplete = &rnWin32SocketTCPAsyncComplete,
        };

        *body = (RnWin32SocketTCPTask) {
            .kind = RnSocketTCPAsync_Read,
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

    rnMemoryArenaRelease(arena, result);

    return 0;
}

#endif // RN_WIN32_NETWORK_ASYNC_C
