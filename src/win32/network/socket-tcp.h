#ifndef PX_WIN32_NETWORK_SOCKET_TCP_H
#define PX_WIN32_NETWORK_SOCKET_TCP_H

#include "address.h"

typedef struct PxWin32SocketTCP
{
    SOCKET            handle;
    PxSockAddrStorage storage;
}
PxWin32SocketTCP;

PxWin32SocketTCP*
pxWin32SocketTCPReserve(PxMemoryArena* arena);

b32
pxWin32SocketTCPCreate(PxWin32SocketTCP* self, PxAddressIP address, u16 port);

b32
pxWin32SocketTCPAccept(PxWin32SocketTCP* self, PxWin32SocketTCP* value);

void
pxWin32SocketTCPDestroy(PxWin32SocketTCP* self);

b32
pxWin32SocketTCPBind(PxWin32SocketTCP* self);

b32
pxWin32SocketTCPBindTo(PxWin32SocketTCP* self, PxAddressIP address, u16 port);

b32
pxWin32SocketTCPListen(PxWin32SocketTCP* self);

b32
pxWin32SocketTCPConnect(PxWin32SocketTCP* self, PxAddressIP address, u16 port);

ssize
pxWin32SocketTCPWrite(PxWin32SocketTCP* self, u8* values, ssize size);

ssize
pxWin32SocketTCPRead(PxWin32SocketTCP* self, u8* values, ssize size);

PxAddressIP
pxWin32SocketTCPGetAddress(PxWin32SocketTCP* self);

u16
pxWin32SocketTCPGetPort(PxWin32SocketTCP* self);

#endif // PX_WIN32_NETWORK_SOCKET_TCP_H
