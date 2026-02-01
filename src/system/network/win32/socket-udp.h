#ifndef RHO_SYSTEM_NETWORK_WIN32_SOCKET_UDP_H
#define RHO_SYSTEM_NETWORK_WIN32_SOCKET_UDP_H

#include "common.h"

typedef struct RWin32SocketUdp
{
    SOCKET            handle;
    RWin32AddrStorage storage;
}
RWin32SocketUdp;

RWin32SocketUdp* rho_win32_socket_udp_reserve(RMemoryArena* arena);

RBool32 rho_win32_socket_udp_create(RWin32SocketUdp* self, RHostIp host);

void rho_win32_socket_udp_destroy(RWin32SocketUdp* self);

RBool32 rho_win32_socket_udp_bind(RWin32SocketUdp* self);

RBool32 rho_win32_socket_udp_bind_as(RWin32SocketUdp* self, RHostIp host);

RInt rho_win32_socket_udp_write(RWin32SocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp host);

RInt rho_win32_socket_udp_read(RWin32SocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp* host);

RHostIp rho_win32_socket_udp_host(RWin32SocketUdp* self);

#endif
