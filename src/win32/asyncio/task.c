#ifndef RN_WIN32_ASYNCIO_TASK_C
#define RN_WIN32_ASYNCIO_TASK_C

#include "./task.h"

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskAccept(RnMemoryArena* arena, RnWin32SocketTCP* socket, RnWin32SocketTCP* value)
{
    ssize length = (sizeof(RnSockAddrStorage) + 16) * 2;

    RnAddressIPKind kind = RnAddressIP_None;

    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    switch (socket->storage.ss_family) {
        case AF_INET:  kind = RnAddressIP_IPv4; break;
        case AF_INET6: kind = RnAddressIP_IPv6; break;

        default: break;
    }

    if (result == 0 || rnSocketTCPCreate(value, rnAddressIPEmpty(kind), 0) == 0)
        return 0;

    *result = (RnWin32AsyncIOTask) {
        .kind = RnAsyncIOEvent_Accept,

        .accept = {
            .socket = socket,
            .value  = value,
            .buffer = rnMemoryArenaReserveManyOf(arena, u8, length),
            .size   = length,
        },
    };

    if (result->accept.buffer != 0) return result;

    rnMemoryArenaRelease(arena, result);

    return 0;
}

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskConnect(RnMemoryArena* arena, RnWin32SocketTCP* socket, RnAddressIP address, u16 port)
{
    RnAddressIPKind kind = RnAddressIP_None;

    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    switch (socket->storage.ss_family) {
        case AF_INET:  kind = RnAddressIP_IPv4; break;
        case AF_INET6: kind = RnAddressIP_IPv6; break;

        default: break;
    }

    if (result == 0 || rnSocketTCPBind(socket) == 0) return 0;

    *result = (RnWin32AsyncIOTask) {
        .kind = RnAsyncIOEvent_Connect,

        .connect = {
            .socket  = socket,
            .address = address,
            .port    = port,
        },
    };

    return result;
}

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskWrite(RnMemoryArena* arena, RnWin32SocketTCP* socket, u8* buffer, ssize size)
{
    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    if (result == 0) return 0;

    *result = (RnWin32AsyncIOTask) {
        .kind = RnAsyncIOEvent_Write,

        .write = {
            .socket = socket,
            .buffer = (WSABUF) {
                .buf = ((char*) buffer),
                .len = size
            },
            .flags  = 0,
        },
    };

    return result;
}

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskRead(RnMemoryArena* arena, RnWin32SocketTCP* socket, u8* buffer, ssize size)
{
    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    if (result == 0) return 0;

    *result = (RnWin32AsyncIOTask) {
        .kind = RnAsyncIOEvent_Read,

        .write = {
            .socket = socket,
            .buffer = (WSABUF) {
                .buf = ((char*) buffer),
                .len = size
            },
            .flags  = 0,
        },
    };

    return result;
}

#endif // RN_WIN32_ASYNCIO_TASK_C
