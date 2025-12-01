#ifndef RN_SYSTEM_NETWORK_SOCKET_UDP_H
#define RN_SYSTEM_NETWORK_SOCKET_UDP_H

#include "./address-ip.h"

typedef void RnSocketUDP;

RnSocketUDP*
rnSocketUDPReserve(RnMemoryArena* arena);

b32
rnSocketUDPCreate(RnSocketUDP* self, RnAddressIPKind kind);

void
rnSocketUDPDestroy(RnSocketUDP* self);

b32
rnSocketUDPBind(RnSocketUDP* self, u16 port);

b32
rnSocketUDPConnect(RnSocketUDP* self, RnAddressIP address, u16 port);

ssize
rnSocketUDPWrite(RnSocketUDP* self, u8* values, ssize size);

ssize
rnSocketUDPWriteHost(RnSocketUDP* self, u8* values, ssize size, RnAddressIP address, u16 port);

ssize
rnSocketUDPRead(RnSocketUDP* self, u8* values, ssize size);

ssize
rnSocketUDPReadHost(RnSocketUDP* self, u8* values, ssize size, RnAddressIP* address, u16* port);

#endif // RN_SYSTEM_NETWORK_SOCKET_UDP_H
