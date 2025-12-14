#ifndef RN_SYSTEM_NETWORK_ASYNC_C
#define RN_SYSTEM_NETWORK_ASYNC_C

#include "./async.h"

#if RN_SYSTEM == RN_SYSTEM_WINDOWS

    #include "../../win32/network/export.c"

    #define __rnSocketTCPAsyncAccept__  rnWin32SocketTCPAsyncAccept
    #define __rnSocketTCPAsyncConnect__ rnWin32SocketTCPAsyncConnect
    #define __rnSocketTCPAsyncWrite__   rnWin32SocketTCPAsyncWrite
    #define __rnSocketTCPAsyncRead__    rnWin32SocketTCPAsyncRead

#else

    #error "Unknown platform"

#endif

RnSocketTCPEvent
rnSocketTCPEventAccept(void* ctxt, RnSocketTCP* listener, RnSocketTCP* socket)
{
    return (RnSocketTCPEvent) {
        .kind = RnSocketTCPAsync_Accept,
        .ctxt = ctxt,

        .accept = {
            .listener = listener,
            .socket   = socket,
        },
    };
}

RnSocketTCPEvent
rnSocketTCPEventConnect(void* ctxt, RnSocketTCP* socket, b32 status)
{
    return (RnSocketTCPEvent) {
        .kind = RnSocketTCPAsync_Connect,
        .ctxt = ctxt,

        .connect = {
            .socket = socket,
            .status = status != 0 ? 1 : 0,
        },
    };
}

RnSocketTCPEvent
rnSocketTCPEventWrite(void* ctxt, RnSocketTCP* socket, u8* values, ssize start, ssize stop)
{
    return (RnSocketTCPEvent) {
        .kind = RnSocketTCPAsync_Write,
        .ctxt = ctxt,

        .write = {
            .socket = socket,
            .values = values,
            .start  = start,
            .stop   = stop,
        },
    };
}

RnSocketTCPEvent
rnSocketTCPEventRead(void* ctxt, RnSocketTCP* socket, u8* values, ssize start, ssize stop)
{
    return (RnSocketTCPEvent) {
        .kind = RnSocketTCPAsync_Read,
        .ctxt = ctxt,

        .read = {
            .socket = socket,
            .values = values,
            .start  = start,
            .stop   = stop,
        },
    };
}

RnSocketTCPEvent
rnSocketTCPEventClose(void* ctxt, RnSocketTCP* socket)
{
    return (RnSocketTCPEvent) {
        .kind = RnSocketTCPAsync_Close,
        .ctxt = ctxt,

        .close = {
            .socket = socket,
        },
    };
}

RnAsyncIOTask*
rnSocketTCPAsyncAccept(RnMemoryArena* arena, void* ctxt, void* proc,
    RnSocketTCP* listener, RnSocketTCP* socket)
{
    return __rnSocketTCPAsyncAccept__(arena, ctxt, proc, listener, socket);
}

RnAsyncIOTask*
rnSocketTCPAsyncConnect(RnMemoryArena* arena, void* ctxt, void* proc,
    RnSocketTCP* socket, RnAddressIP address, u16 port)
{
    return __rnSocketTCPAsyncConnect__(arena, ctxt, proc, socket, address, port);
}

RnAsyncIOTask*
rnSocketTCPAsyncWrite(RnMemoryArena* arena, void* ctxt, void* proc,
    RnSocketTCP* socket, u8* values, ssize start, ssize stop)
{
    return __rnSocketTCPAsyncWrite__(arena, ctxt, proc, socket, values, start, stop);
}

RnAsyncIOTask*
rnSocketTCPAsyncRead(RnMemoryArena* arena, void* ctxt, void* proc,
    RnSocketTCP* socket, u8* values, ssize start, ssize stop)
{
    return __rnSocketTCPAsyncRead__(arena, ctxt, proc, socket, values, start, stop);
}

#endif // RN_SYSTEM_NETWORK_ASYNC_C
