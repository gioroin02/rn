#ifndef RN_SYSTEM_NETWORK_SOCKET_TCP_H
#define RN_SYSTEM_NETWORK_SOCKET_TCP_H

#include "./address-ip.h"

typedef void RnSocketTCP;

RnSocketTCP*
rnSocketTCPReserve(RnMemoryArena* arena);

b32
rnSocketTCPCreate(RnSocketTCP* self, RnAddressIPKind kind);

b32
rnSocketTCPAccept(RnSocketTCP* self, RnSocketTCP* value);

void
rnSocketTCPDestroy(RnSocketTCP* self);

b32
rnSocketTCPBindAndListen(RnSocketTCP* self, u16 port);

b32
rnSocketTCPConnect(RnSocketTCP* self, RnAddressIP address, u16 port);

ssize
rnSocketTCPWrite(RnSocketTCP* self, u8* values, ssize size);

ssize
rnSocketTCPRead(RnSocketTCP* self, u8* values, ssize size);

#endif // RN_SYSTEM_NETWORK_SOCKET_TCP_H
