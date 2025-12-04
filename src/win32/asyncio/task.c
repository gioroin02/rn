#ifndef RN_WIN32_ASYNCIO_TASK_C
#define RN_WIN32_ASYNCIO_TASK_C

#include "./task.h"

RnWin32AsyncIOTask*
rnWin32AsyncIOTaskAccept(RnMemoryArena* arena, RnWin32SocketTCP* listener, RnWin32SocketTCP* socket)
{
    ssize size = (sizeof(RnSockAddrStorage) + 16) * 2;

    RnAddressIPKind kind = RnAddressIP_None;

    RnWin32AsyncIOTask* result =
        rnMemoryArenaReserveOneOf(arena, RnWin32AsyncIOTask);

    switch (listener->storage.ss_family) {
        case AF_INET:  kind = RnAddressIP_IPv4; break;
        case AF_INET6: kind = RnAddressIP_IPv6; break;

        default: break;
    }

    if (result == 0 || rnWin32SocketTCPCreate(socket, kind) == 0)
        return 0;

    *result = (RnWin32AsyncIOTask) {
        .kind = RnAsyncIOEvent_Accept,

        .accept = {
            .listener = listener,
            .socket   = socket,
            .buffer   = rnMemoryArenaReserveManyOf(arena, u8, size),
            .size     = size,
        },
    };

    if (result->accept.buffer != 0) return result;

    rnMemoryArenaRelease(arena, result);

    return 0;
}

#endif // RN_WIN32_ASYNCIO_TASK_C
