#ifndef P_SYSTEM_NETWORK_SOCKET_UDP_C
#define P_SYSTEM_NETWORK_SOCKET_UDP_C

#include "socket-udp.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PSocketUdp__ PWin32SocketUdp

    #define __pSocketUdpReserve__ pWin32SocketUdpReserve
    #define __pSocketUdpCreate__  pWin32SocketUdpCreate
    #define __pSocketUdpDestroy__ pWin32SocketUdpDestroy
    #define __pSocketUdpBind__    pWin32SocketUdpBind
    #define __pSocketUdpBindAs__  pWin32SocketUdpBindAs
    #define __pSocketUdpWrite__   pWin32SocketUdpWrite
    #define __pSocketUdpRead__    pWin32SocketUdpRead
    #define __pSocketUdpGetHost__ pWin32SocketUdpGetHost

#elif P_SYSTEM == P_SYSTEM_LINUX

    #include "linux/export.c"

    #define __PSocketUdp__ PLinuxSocketUdp

    #define __pSocketUdpReserve__ pLinuxSocketUdpReserve
    #define __pSocketUdpCreate__  pLinuxSocketUdpCreate
    #define __pSocketUdpDestroy__ pLinuxSocketUdpDestroy
    #define __pSocketUdpBind__    pLinuxSocketUdpBind
    #define __pSocketUdpBindAs__  pLinuxSocketUdpBindAs
    #define __pSocketUdpWrite__   pLinuxSocketUdpWrite
    #define __pSocketUdpRead__    pLinuxSocketUdpRead
    #define __pSocketUdpGetHost__ pLinuxSocketUdpGetHost

#else

    #error "Unknown platform"

#endif

PSocketUdp* pSocketUdpReserve(PMemoryArena* arena)
{
    return (PSocketUdp*) __pSocketUdpReserve__(arena);
}

Bool pSocketUdpCreate(PSocketUdp* self, PHostIp host)
{
    return __pSocketUdpCreate__((__PSocketUdp__*) self, host);
}

void pSocketUdpDestroy(PSocketUdp* self)
{
    return __pSocketUdpDestroy__((__PSocketUdp__*) self);
}

Bool pSocketUdpBind(PSocketUdp* self)
{
    return __pSocketUdpBind__((__PSocketUdp__*) self);
}

Bool pSocketUdpBindAs(PSocketUdp* self, PHostIp host)
{
    return __pSocketUdpBindAs__((__PSocketUdp__*) self, host);
}

Int pSocketUdpWrite(PSocketUdp* self, U8* pntr, Int start, Int stop, PHostIp host)
{
    return __pSocketUdpWrite__((__PSocketUdp__*) self, pntr, start, stop, host);
}

Int pSocketUdpRead(PSocketUdp* self, U8* pntr, Int start, Int stop, PHostIp* host)
{
    return __pSocketUdpRead__((__PSocketUdp__*) self, pntr, start, stop, host);
}

PHostIp pSocketUdpGetHost(PSocketUdp* self)
{
    return __pSocketUdpGetHost__((__PSocketUdp__*) self);
}

#endif
