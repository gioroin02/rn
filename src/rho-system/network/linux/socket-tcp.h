#ifndef RHO_SYSTEM_NETWORK_LINUX_SOCKET_TCP_H
#define RHO_SYSTEM_NETWORK_LINUX_SOCKET_TCP_H

#include "common.h"

typedef struct RLinuxSocketTcp
{
    RInt              handle;
    RLinuxAddrStorage storage;
}
RLinuxSocketTcp;

RLinuxSocketTcp* rho_linux_socket_tcp_reserve(RMemoryArena* arena);

RBool32 rho_linux_socket_tcp_create(RLinuxSocketTcp* self, RHostIp host);

RBool32 rho_linux_socket_tcp_accept(RLinuxSocketTcp* self, RLinuxSocketTcp* value);

void rho_linux_socket_tcp_destroy(RLinuxSocketTcp* self);

RBool32 rho_linux_socket_tcp_bind(RLinuxSocketTcp* self);

RBool32 rho_linux_socket_tcp_bind_as(RLinuxSocketTcp* self, RHostIp host);

RBool32 rho_linux_socket_tcp_listen(RLinuxSocketTcp* self);

RBool32 rho_linux_socket_tcp_connect(RLinuxSocketTcp* self, RHostIp host);

RInt rho_linux_socket_tcp_write(RLinuxSocketTcp* self, RUint8* pntr, RInt start, RInt stop);

RInt rho_linux_socket_tcp_read(RLinuxSocketTcp* self, RUint8* pntr, RInt start, RInt stop);

RHostIp rho_linux_socket_tcp_host(RLinuxSocketTcp* self);

#endif
