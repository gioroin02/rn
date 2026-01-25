#ifndef P_SYSTEM_NETWORK_SOCKET_TCP_C
#define P_SYSTEM_NETWORK_SOCKET_TCP_C

#include "socket-tcp.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PSocketTcp__ PWin32SocketTcp

    #define __pSocketTcpReserve__ pWin32SocketTcpReserve
    #define __pSocketTcpCreate__  pWin32SocketTcpCreate
    #define __pSocketTcpAccept__  pWin32SocketTcpAccept
    #define __pSocketTcpDestroy__ pWin32SocketTcpDestroy
    #define __pSocketTcpBind__    pWin32SocketTcpBind
    #define __pSocketTcpBindAs__  pWin32SocketTcpBindAs
    #define __pSocketTcpListen__  pWin32SocketTcpListen
    #define __pSocketTcpConnect__ pWin32SocketTcpConnect
    #define __pSocketTcpWrite__   pWin32SocketTcpWrite
    #define __pSocketTcpRead__    pWin32SocketTcpRead
    #define __pSocketTcpGetHost__ pWin32SocketTcpGetHost

#elif P_SYSTEM == P_SYSTEM_LINUX

    #include "linux/export.c"

    #define __PSocketTcp__ PLinuxSocketTcp

    #define __pSocketTcpReserve__ pLinuxSocketTcpReserve
    #define __pSocketTcpCreate__  pLinuxSocketTcpCreate
    #define __pSocketTcpAccept__  pLinuxSocketTcpAccept
    #define __pSocketTcpDestroy__ pLinuxSocketTcpDestroy
    #define __pSocketTcpBind__    pLinuxSocketTcpBind
    #define __pSocketTcpBindAs__  pLinuxSocketTcpBindAs
    #define __pSocketTcpListen__  pLinuxSocketTcpListen
    #define __pSocketTcpConnect__ pLinuxSocketTcpConnect
    #define __pSocketTcpWrite__   pLinuxSocketTcpWrite
    #define __pSocketTcpRead__    pLinuxSocketTcpRead
    #define __pSocketTcpGetHost__ pLinuxSocketTcpGetHost

#else

    #error "Unknown platform"

#endif

PSocketTcp* pSocketTcpReserve(PMemoryArena* arena)
{
    return (PSocketTcp*)  __pSocketTcpReserve__(arena);
}

B32 pSocketTcpCreate(PSocketTcp* self, PHostIp host)
{
    return __pSocketTcpCreate__((__PSocketTcp__*) self, host);
}

B32 pSocketTcpAccept(PSocketTcp* self, PSocketTcp* value)
{
    return __pSocketTcpAccept__((__PSocketTcp__*) self, (__PSocketTcp__*) value);
}

void pSocketTcpDestroy(PSocketTcp* self)
{
    return __pSocketTcpDestroy__((__PSocketTcp__*) self);
}

B32 pSocketTcpBind(PSocketTcp* self)
{
    return __pSocketTcpBind__((__PSocketTcp__*) self);
}

B32 pSocketTcpBindAs(PSocketTcp* self, PHostIp host)
{
    return __pSocketTcpBindAs__((__PSocketTcp__*) self, host);
}

B32 pSocketTcpListen(PSocketTcp* self)
{
    return __pSocketTcpListen__((__PSocketTcp__*) self);
}

B32 pSocketTcpConnect(PSocketTcp* self, PHostIp host)
{
    return __pSocketTcpConnect__((__PSocketTcp__*) self, host);
}

Int
pSocketTcpWrite(PSocketTcp* self, U8* pntr, Int start, Int stop)
{
    return __pSocketTcpWrite__((__PSocketTcp__*) self, pntr, start, stop);
}

Int pSocketTcpRead(PSocketTcp* self, U8* pntr, Int start, Int stop)
{
    return __pSocketTcpRead__((__PSocketTcp__*) self, pntr, start, stop);
}

PHostIp pSocketTcpGetHost(PSocketTcp* self)
{
    return __pSocketTcpGetHost__((__PSocketTcp__*) self);
}

#endif
