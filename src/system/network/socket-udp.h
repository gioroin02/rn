#ifndef RHO_SYSTEM_NETWORK_SOCKET_UDP_H
#define RHO_SYSTEM_NETWORK_SOCKET_UDP_H

#include "address-ip.h"

typedef struct RSocketUdp { RUint8 __private__; } RSocketUdp;

RSocketUdp* rho_socket_udp_reserve(RMemoryArena* arena);

RBool32 rho_socket_udp_create(RSocketUdp* self, RHostIp host);

void rho_socket_udp_destroy(RSocketUdp* self);

RBool32 rho_socket_udp_bind(RSocketUdp* self);

RBool32 rho_socket_udp_bind_as(RSocketUdp* self, RHostIp host);

RInt rho_socket_udp_write(RSocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp host);

RInt rho_socket_udp_read(RSocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp* host);

RHostIp rho_socket_udp_host(RSocketUdp* self);

#endif
