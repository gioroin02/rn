#ifndef RHO_SYSTEM_NETWORK_SOCKET_TCP_H
#define RHO_SYSTEM_NETWORK_SOCKET_TCP_H

#include "address-ip.h"

typedef struct RSocketTcp { RUint8 __private__; } RSocketTcp;

RSocketTcp* rho_socket_tcp_reserve(RMemoryArena* arena);

RBool32 rho_socket_tcp_create(RSocketTcp* self, RHostIp host);

RBool32 rho_socket_tcp_accept(RSocketTcp* self, RSocketTcp* value);

void rho_socket_tcp_destroy(RSocketTcp* self);

RBool32 rho_socket_tcp_bind(RSocketTcp* self);

RBool32 rho_socket_tcp_bind_as(RSocketTcp* self, RHostIp host);

RBool32 rho_socket_tcp_listen(RSocketTcp* self);

RBool32 rho_socket_tcp_connect(RSocketTcp* self, RHostIp host);

RInt rho_socket_tcp_write(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop);

RInt rho_socket_tcp_read(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop);

RHostIp rho_socket_tcp_host(RSocketTcp* self);

#endif
