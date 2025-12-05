#ifndef RN_WIN32_ASYNCIO_TASK_C
#define RN_WIN32_ASYNCIO_TASK_C

#include "./task.h"

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskAccept(RnMemoryArena* arena, RnWin32SocketTCP* self, RnWin32SocketTCP* value)
{
    ssize size = (sizeof(RnSockAddrStorage) + 16) * 2;

    RnAddressIPKind kind = RnAddressIP_None;

    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    switch (self->storage.ss_family) {
        case AF_INET:  kind = RnAddressIP_IPv4; break;
        case AF_INET6: kind = RnAddressIP_IPv6; break;

        default: break;
    }

    if (result == 0 || rnWin32SocketTCPCreate(value, kind) == 0)
        return 0;

    *result = (RnWin32AsyncIOTask) {
        .kind = RnAsyncIOEvent_Accept,

        .accept = {
            .self   = self,
            .value  = value,
            .buffer = rnMemoryArenaReserveManyOf(arena, u8, size),
            .size   = size,
        },
    };

    if (result->accept.buffer != 0) return result;

    rnMemoryArenaRelease(arena, result);

    return 0;
}

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskConnect(RnMemoryArena* arena, RnWin32SocketTCP* self, RnAddressIP address, u16 port)
{
    RnAddressIPKind kind = RnAddressIP_None;

    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    switch (self->storage.ss_family) {
        case AF_INET:  kind = RnAddressIP_IPv4; break;
        case AF_INET6: kind = RnAddressIP_IPv6; break;

        default: break;
    }

    if (result == 0 || rnWin32SocketTCPBind(self, 0) == 0) return 0;

    *result = (RnWin32AsyncIOTask) {
        .kind = RnAsyncIOEvent_Connect,

        .connect = {
            .self    = self,
            .address = address,
            .port    = port,
        },
    };

    return result;
}

#endif // RN_WIN32_ASYNCIO_TASK_C
