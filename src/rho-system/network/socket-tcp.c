#ifndef RHO_SYSTEM_NETWORK_SOCKET_TCP_C
#define RHO_SYSTEM_NETWORK_SOCKET_TCP_C

#include "socket-tcp.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RSocketTcp__ RWin32SocketTcp

    #define __rho_socket_tcp_reserve__ rho_win32_socket_tcp_reserve
    #define __rho_socket_tcp_create__  rho_win32_socket_tcp_create
    #define __rho_socket_tcp_accept__  rho_win32_socket_tcp_accept
    #define __rho_socket_tcp_destroy__ rho_win32_socket_tcp_destroy
    #define __rho_socket_tcp_bind__    rho_win32_socket_tcp_bind
    #define __rho_socket_tcp_bind_as__ rho_win32_socket_tcp_bind_as
    #define __rho_socket_tcp_listen__  rho_win32_socket_tcp_listen
    #define __rho_socket_tcp_connect__ rho_win32_socket_tcp_connect
    #define __rho_socket_tcp_write__   rho_win32_socket_tcp_write
    #define __rho_socket_tcp_read__    rho_win32_socket_tcp_read
    #define __rho_socket_tcp_host__    rho_win32_socket_tcp_host

#elif RHO_SYSTEM == RHO_SYSTEM_LINUX

    #include "linux/export.c"

    #define __RSocketTcp__ RLinuxSocketTcp

    #define __rho_socket_tcp_reserve__ rho_linux_socket_tcp_reserve
    #define __rho_socket_tcp_create__  rho_linux_socket_tcp_create
    #define __rho_socket_tcp_accept__  rho_linux_socket_tcp_accept
    #define __rho_socket_tcp_destroy__ rho_linux_socket_tcp_destroy
    #define __rho_socket_tcp_bind__    rho_linux_socket_tcp_bind
    #define __rho_socket_tcp_bind_as__ rho_linux_socket_tcp_bind_as
    #define __rho_socket_tcp_listen__  rho_linux_socket_tcp_listen
    #define __rho_socket_tcp_connect__ rho_linux_socket_tcp_connect
    #define __rho_socket_tcp_write__   rho_linux_socket_tcp_write
    #define __rho_socket_tcp_read__    rho_linux_socket_tcp_read
    #define __rho_socket_tcp_host__    rho_linux_socket_tcp_host

#else

    #error "Unknown platform"

#endif

RSocketTcp* rho_socket_tcp_reserve(RMemoryArena* arena)
{
    return (RSocketTcp*)  __rho_socket_tcp_reserve__(arena);
}

RBool32 rho_socket_tcp_create(RSocketTcp* self, RHostIp host)
{
    return __rho_socket_tcp_create__((__RSocketTcp__*) self, host);
}

RBool32 rho_socket_tcp_accept(RSocketTcp* self, RSocketTcp* value)
{
    return __rho_socket_tcp_accept__((__RSocketTcp__*) self, (__RSocketTcp__*) value);
}

void rho_socket_tcp_destroy(RSocketTcp* self)
{
    return __rho_socket_tcp_destroy__((__RSocketTcp__*) self);
}

RBool32 rho_socket_tcp_bind(RSocketTcp* self)
{
    return __rho_socket_tcp_bind__((__RSocketTcp__*) self);
}

RBool32 rho_socket_tcp_bind_as(RSocketTcp* self, RHostIp host)
{
    return __rho_socket_tcp_bind_as__((__RSocketTcp__*) self, host);
}

RBool32 rho_socket_tcp_listen(RSocketTcp* self)
{
    return __rho_socket_tcp_listen__((__RSocketTcp__*) self);
}

RBool32 rho_socket_tcp_connect(RSocketTcp* self, RHostIp host)
{
    return __rho_socket_tcp_connect__((__RSocketTcp__*) self, host);
}

RInt rho_socket_tcp_write(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop)
{
    return __rho_socket_tcp_write__((__RSocketTcp__*) self, pntr, start, stop);
}

RInt rho_socket_tcp_read(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop)
{
    return __rho_socket_tcp_read__((__RSocketTcp__*) self, pntr, start, stop);
}

RHostIp rho_socket_tcp_host(RSocketTcp* self)
{
    return __rho_socket_tcp_host__((__RSocketTcp__*) self);
}

#endif
