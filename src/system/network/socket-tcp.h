#ifndef PX_SYSTEM_NETWORK_SOCKET_TCP_H
#define PX_SYSTEM_NETWORK_SOCKET_TCP_H

#include "address-ip.h"

typedef void PxSocketTCP;

PxSocketTCP*
pxSocketTCPReserve(PxMemoryArena* arena);

b32
pxSocketTCPCreate(PxSocketTCP* self, PxAddressIP address, u16 port);

b32
pxSocketTCPAccept(PxSocketTCP* self, PxSocketTCP* value);

void
pxSocketTCPDestroy(PxSocketTCP* self);

b32
pxSocketTCPBind(PxSocketTCP* self);

b32
pxSocketTCPBindTo(PxSocketTCP* self, PxAddressIP address, u16 port);

b32
pxSocketTCPListen(PxSocketTCP* self);

b32
pxSocketTCPConnect(PxSocketTCP* self, PxAddressIP address, u16 port);

ssize
pxSocketTCPWrite(PxSocketTCP* self, u8* values, ssize size);

ssize
pxSocketTCPRead(PxSocketTCP* self, u8* values, ssize size);

PxAddressIP
pxSocketTCPGetAddress(PxSocketTCP* self);

u16
pxSocketTCPGetPort(PxSocketTCP* self);

#endif // PX_SYSTEM_NETWORK_SOCKET_TCP_H
