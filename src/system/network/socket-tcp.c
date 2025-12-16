#ifndef PX_SYSTEM_NETWORK_SOCKET_TCP_C
#define PX_SYSTEM_NETWORK_SOCKET_TCP_C

#include "socket-tcp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../win32/network/export.c"

    #define __pxSocketTCPReserve__ pxWin32SocketTCPReserve
    #define __pxSocketTCPCreate__  pxWin32SocketTCPCreate
    #define __pxSocketTCPAccept__  pxWin32SocketTCPAccept
    #define __pxSocketTCPDestroy__ pxWin32SocketTCPDestroy
    #define __pxSocketTCPBind__    pxWin32SocketTCPBind
    #define __pxSocketTCPBindTo__  pxWin32SocketTCPBindTo
    #define __pxSocketTCPListen__  pxWin32SocketTCPListen
    #define __pxSocketTCPConnect__ pxWin32SocketTCPConnect
    #define __pxSocketTCPWrite__   pxWin32SocketTCPWrite
    #define __pxSocketTCPRead__    pxWin32SocketTCPRead

    #define __pxSocketTCPGetAddress__ pxWin32SocketTCPGetAddress
    #define __pxSocketTCPGetPort__    pxWin32SocketTCPGetPort

#else

    #error "Unknown platform"

#endif

PxSocketTCP*
pxSocketTCPReserve(PxMemoryArena* arena)
{
    return __pxSocketTCPReserve__(arena);
}

b32
pxSocketTCPCreate(PxSocketTCP* self, PxAddressIP address, u16 port)
{
    return __pxSocketTCPCreate__(self, address, port);
}

b32
pxSocketTCPAccept(PxSocketTCP* self, PxSocketTCP* value)
{
    return __pxSocketTCPAccept__(self, value);
}

void
pxSocketTCPDestroy(PxSocketTCP* self)
{
    return __pxSocketTCPDestroy__(self);
}

b32
pxSocketTCPBind(PxSocketTCP* self)
{
    return __pxSocketTCPBind__(self);
}

b32
pxSocketTCPBindTo(PxSocketTCP* self, PxAddressIP address, u16 port)
{
    return __pxSocketTCPBindTo__(self, address, port);
}

b32
pxSocketTCPListen(PxSocketTCP* self)
{
    return __pxSocketTCPListen__(self);
}

b32
pxSocketTCPConnect(PxSocketTCP* self, PxAddressIP address, u16 port)
{
    return __pxSocketTCPConnect__(self, address, port);
}

ssize
pxSocketTCPWrite(PxSocketTCP* self, u8* values, ssize size)
{
    return __pxSocketTCPWrite__(self, values, size);
}

ssize
pxSocketTCPRead(PxSocketTCP* self, u8* values, ssize size)
{
    return __pxSocketTCPRead__(self, values, size);
}

PxAddressIP
pxSocketTCPGetAddress(PxSocketTCP* self)
{
    return __pxSocketTCPGetAddress__(self);
}

u16
pxSocketTCPGetPort(PxSocketTCP* self)
{
    return __pxSocketTCPGetPort__(self);
}

#endif // PX_SYSTEM_NETWORK_SOCKET_TCP_C
