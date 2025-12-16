#ifndef PX_SYSTEM_NETWORK_ASYNC_C
#define PX_SYSTEM_NETWORK_ASYNC_C

#include "async.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../win32/network/export.c"

    #define __pxSocketTCPAsyncAccept__  pxWin32SocketTCPAsyncAccept
    #define __pxSocketTCPAsyncConnect__ pxWin32SocketTCPAsyncConnect
    #define __pxSocketTCPAsyncWrite__   pxWin32SocketTCPAsyncWrite
    #define __pxSocketTCPAsyncRead__    pxWin32SocketTCPAsyncRead

#else

    #error "Unknown platform"

#endif

PxSocketTCPEvent
pxSocketTCPEventAccept(void* ctxt, PxSocketTCP* listener, PxSocketTCP* socket)
{
    return (PxSocketTCPEvent) {
        .kind = PxSocketTCPAsync_Accept,
        .ctxt = ctxt,

        .accept = {
            .listener = listener,
            .socket   = socket,
        },
    };
}

PxSocketTCPEvent
pxSocketTCPEventConnect(void* ctxt, PxSocketTCP* socket, b32 status)
{
    return (PxSocketTCPEvent) {
        .kind = PxSocketTCPAsync_Connect,
        .ctxt = ctxt,

        .connect = {
            .socket = socket,
            .status = status != 0 ? 1 : 0,
        },
    };
}

PxSocketTCPEvent
pxSocketTCPEventWrite(void* ctxt, PxSocketTCP* socket, u8* values, ssize start, ssize stop)
{
    return (PxSocketTCPEvent) {
        .kind = PxSocketTCPAsync_Write,
        .ctxt = ctxt,

        .write = {
            .socket = socket,
            .values = values,
            .start  = start,
            .stop   = stop,
        },
    };
}

PxSocketTCPEvent
pxSocketTCPEventRead(void* ctxt, PxSocketTCP* socket, u8* values, ssize start, ssize stop)
{
    return (PxSocketTCPEvent) {
        .kind = PxSocketTCPAsync_Read,
        .ctxt = ctxt,

        .read = {
            .socket = socket,
            .values = values,
            .start  = start,
            .stop   = stop,
        },
    };
}

PxSocketTCPEvent
pxSocketTCPEventClose(void* ctxt, PxSocketTCP* socket)
{
    return (PxSocketTCPEvent) {
        .kind = PxSocketTCPAsync_Close,
        .ctxt = ctxt,

        .close = {
            .socket = socket,
        },
    };
}

PxAsyncIOTask*
pxSocketTCPAsyncAccept(PxMemoryArena* arena, void* ctxt, void* proc,
    PxSocketTCP* listener, PxSocketTCP* socket)
{
    return __pxSocketTCPAsyncAccept__(arena, ctxt, proc, listener, socket);
}

PxAsyncIOTask*
pxSocketTCPAsyncConnect(PxMemoryArena* arena, void* ctxt, void* proc,
    PxSocketTCP* socket, PxAddressIP address, u16 port)
{
    return __pxSocketTCPAsyncConnect__(arena, ctxt, proc, socket, address, port);
}

PxAsyncIOTask*
pxSocketTCPAsyncWrite(PxMemoryArena* arena, void* ctxt, void* proc,
    PxSocketTCP* socket, u8* values, ssize start, ssize stop)
{
    return __pxSocketTCPAsyncWrite__(arena, ctxt, proc, socket, values, start, stop);
}

PxAsyncIOTask*
pxSocketTCPAsyncRead(PxMemoryArena* arena, void* ctxt, void* proc,
    PxSocketTCP* socket, u8* values, ssize start, ssize stop)
{
    return __pxSocketTCPAsyncRead__(arena, ctxt, proc, socket, values, start, stop);
}

#endif // PX_SYSTEM_NETWORK_ASYNC_C
