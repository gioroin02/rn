#ifndef PX_SYSTEM_NETWORK_SOCKET_UDP_C
#define PX_SYSTEM_NETWORK_SOCKET_UDP_C

#include "socket-udp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../win32/network/export.c"

    #define __pxSocketUDPReserve__ pxWin32SocketUDPReserve
    #define __pxSocketUDPCreate__  pxWin32SocketUDPCreate
    #define __pxSocketUDPDestroy__ pxWin32SocketUDPDestroy
    #define __pxSocketUDPBind__    pxWin32SocketUDPBind
    #define __pxSocketUDPBindTo__  pxWin32SocketUDPBindTo
    #define __pxSocketUDPWrite__   pxWin32SocketUDPWrite
    #define __pxSocketUDPRead__    pxWin32SocketUDPRead

    #define __pxSocketUDPGetAddress__ pxWin32SocketUDPGetAddress
    #define __pxSocketUDPGetPort__    pxWin32SocketUDPGetPort

#else

    #error "Unknown platform"

#endif

PxSocketUDP*
pxSocketUDPReserve(PxMemoryArena* arena)
{
    return __pxSocketUDPReserve__(arena);
}

b32
pxSocketUDPCreate(PxSocketUDP* self, PxAddressIP address, u16 port)
{
    return __pxSocketUDPCreate__(self, address, port);
}

void
pxSocketUDPDestroy(PxSocketUDP* self)
{
    return __pxSocketUDPDestroy__(self);
}

b32
pxSocketUDPBind(PxSocketUDP* self)
{
    return __pxSocketUDPBind__(self);
}

b32
pxSocketUDPBindTo(PxSocketUDP* self, PxAddressIP address, u16 port)
{
    return __pxSocketUDPBindTo__(self, address, port);
}

ssize
pxSocketUDPWrite(PxSocketUDP* self, u8* values, ssize size, PxAddressIP address, u16 port)
{
    return __pxSocketUDPWrite__(self, values, size, address, port);
}

ssize
pxSocketUDPRead(PxSocketUDP* self, u8* values, ssize size, PxAddressIP* address, u16* port)
{
    return __pxSocketUDPRead__(self, values, size, address, port);
}

PxAddressIP
pxSocketUDPGetAddress(PxSocketUDP* self)
{
    return __pxSocketUDPGetAddress__(self);
}

u16
pxSocketUDPGetPort(PxSocketUDP* self)
{
    return __pxSocketUDPGetPort__(self);
}

#endif // PX_SYSTEM_NETWORK_SOCKET_UDP_C
