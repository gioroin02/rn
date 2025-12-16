#ifndef PX_SYSTEM_NETWORK_SOCKET_UDP_H
#define PX_SYSTEM_NETWORK_SOCKET_UDP_H

#include "address-ip.h"

typedef void PxSocketUDP;

PxSocketUDP*
pxSocketUDPReserve(PxMemoryArena* arena);

b32
pxSocketUDPCreate(PxSocketUDP* self, PxAddressIP address, u16 port);

void
pxSocketUDPDestroy(PxSocketUDP* self);

b32
pxSocketUDPBind(PxSocketUDP* self);

b32
pxSocketUDPBindTo(PxSocketUDP* self, PxAddressIP address, u16 port);

ssize
pxSocketUDPWrite(PxSocketUDP* self, u8* values, ssize size, PxAddressIP address, u16 port);

ssize
pxSocketUDPRead(PxSocketUDP* self, u8* values, ssize size, PxAddressIP* address, u16* port);

PxAddressIP
pxSocketUDPGetAddress(PxSocketUDP* self);

u16
pxSocketUDPGetPort(PxSocketUDP* self);

#endif // PX_SYSTEM_NETWORK_SOCKET_UDP_H
