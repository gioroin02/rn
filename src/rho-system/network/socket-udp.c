#ifndef RHO_SYSTEM_NETWORK_SOCKET_UDP_C
#define RHO_SYSTEM_NETWORK_SOCKET_UDP_C

#include "socket-udp.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RSocketUdp__ RWin32SocketUdp

    #define __rho_socket_udp_reserve__ rho_win32_socket_udp_reserve
    #define __rho_socket_udp_create__  rho_win32_socket_udp_create
    #define __rho_socket_udp_destroy__ rho_win32_socket_udp_destroy
    #define __rho_socket_udp_bind__    rho_win32_socket_udp_bind
    #define __rho_socket_udp_bind_as__ rho_win32_socket_udp_bind_as
    #define __rho_socket_udp_write__   rho_win32_socket_udp_write
    #define __rho_socket_udp_read__    rho_win32_socket_udp_read
    #define __rho_socket_udp_host__    rho_win32_socket_udp_host

#elif RHO_SYSTEM == RHO_SYSTEM_LINUX

    #include "linux/export.c"

    #define __RSocketUdp__ RLinuxSocketUdp

    #define __rho_socket_udp_reserve__ rho_linux_socket_udp_reserve
    #define __rho_socket_udp_create__  rho_linux_socket_udp_create
    #define __rho_socket_udp_destroy__ rho_linux_socket_udp_destroy
    #define __rho_socket_udp_bind__    rho_linux_socket_udp_bind
    #define __rho_socket_udp_bind_as__ rho_linux_socket_udp_bind_as
    #define __rho_socket_udp_write__   rho_linux_socket_udp_write
    #define __rho_socket_udp_read__    rho_linux_socket_udp_read
    #define __rho_socket_udp_host__    rho_linux_socket_udp_host

#else

    #error "Unknown platform"

#endif

RSocketUdp* rho_socket_udp_reserve(RMemoryArena* arena)
{
    return (RSocketUdp*) __rho_socket_udp_reserve__(arena);
}

RBool32 rho_socket_udp_create(RSocketUdp* self, RHostIp host)
{
    return __rho_socket_udp_create__((__RSocketUdp__*) self, host);
}

void rho_socket_udp_destroy(RSocketUdp* self)
{
    return __rho_socket_udp_destroy__((__RSocketUdp__*) self);
}

RBool32 rho_socket_udp_bind(RSocketUdp* self)
{
    return __rho_socket_udp_bind__((__RSocketUdp__*) self);
}

RBool32 rho_socket_udp_bind_as(RSocketUdp* self, RHostIp host)
{
    return __rho_socket_udp_bind_as__((__RSocketUdp__*) self, host);
}

RInt rho_socket_udp_write(RSocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp host)
{
    return __rho_socket_udp_write__((__RSocketUdp__*) self, pntr, start, stop, host);
}

RInt rho_socket_udp_read(RSocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp* host)
{
    return __rho_socket_udp_read__((__RSocketUdp__*) self, pntr, start, stop, host);
}

RHostIp rho_socket_udp_host(RSocketUdp* self)
{
    return __rho_socket_udp_host__((__RSocketUdp__*) self);
}

#endif
