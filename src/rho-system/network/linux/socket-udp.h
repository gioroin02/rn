#ifndef RHO_SYSTEM_NETWORK_LINUX_SOCKET_UDP_H
#define RHO_SYSTEM_NETWORK_LINUX_SOCKET_UDP_H

#include "common.h"

typedef struct RLinuxSocketUdp
{
    RInt              handle;
    RLinuxAddrStorage storage;
}
RLinuxSocketUdp;

RLinuxSocketUdp* rho_linux_socket_udp_reserve(RMemoryArena* arena);

RBool32 rho_linux_socket_udp_create(RLinuxSocketUdp* self, RHostIp host);

void rho_linux_socket_udp_destroy(RLinuxSocketUdp* self);

RBool32 rho_linux_socket_udp_bind(RLinuxSocketUdp* self);

RBool32 rho_linux_socket_udp_bind_as(RLinuxSocketUdp* self, RHostIp host);

RInt rho_linux_socket_udp_write(RLinuxSocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp host);

RInt rho_linux_socket_udp_read(RLinuxSocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp* host);

RHostIp rho_linux_socket_udp_host(RLinuxSocketUdp* self);

#endif
