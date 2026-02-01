#ifndef RHO_SYSTEM_NETWORK_WIN32_SOCKET_TCP_H
#define RHO_SYSTEM_NETWORK_WIN32_SOCKET_TCP_H

#include "common.h"

typedef struct RWin32SocketTcp
{
    SOCKET            handle;
    RWin32AddrStorage storage;
}
RWin32SocketTcp;

RWin32SocketTcp* rho_win32_socket_tcp_reserve(RMemoryArena* arena);

RBool32 rho_win32_socket_tcp_create(RWin32SocketTcp* self, RHostIp host);

RBool32 rho_win32_socket_tcp_accept(RWin32SocketTcp* self, RWin32SocketTcp* value);

void rho_win32_socket_tcp_destroy(RWin32SocketTcp* self);

RBool32 rho_win32_socket_tcp_bind(RWin32SocketTcp* self);

RBool32 rho_win32_socket_tcp_bind_as(RWin32SocketTcp* self, RHostIp host);

RBool32 rho_win32_socket_tcp_listen(RWin32SocketTcp* self);

RBool32 rho_win32_socket_tcp_connect(RWin32SocketTcp* self, RHostIp host);

RInt rho_win32_socket_tcp_write(RWin32SocketTcp* self, RUint8* pntr, RInt start, RInt stop);

RInt rho_win32_socket_tcp_read(RWin32SocketTcp* self, RUint8* pntr, RInt start, RInt stop);

RHostIp rho_win32_socket_tcp_host(RWin32SocketTcp* self);

#endif
