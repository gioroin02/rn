#ifndef PX_WIN32_NETWORK_SOCKET_UDP_H
#define PX_WIN32_NETWORK_SOCKET_UDP_H

#include "address.h"

typedef struct PxWin32SocketUDP
{
    SOCKET            handle;
    PxSockAddrStorage storage;
}
PxWin32SocketUDP;

PxWin32SocketUDP*
pxWin32SocketUDPReserve(PxMemoryArena* arena);

b32
pxWin32SocketUDPCreate(PxWin32SocketUDP* self, PxAddressIP address, u16 port);

void
pxWin32SocketUDPDestroy(PxWin32SocketUDP* self);

b32
pxWin32SocketUDPBind(PxWin32SocketUDP* self);

b32
pxWin32SocketUDPBindTo(PxWin32SocketUDP* self, PxAddressIP address, u16 port);

ssize
pxWin32SocketUDPWrite(PxWin32SocketUDP* self, u8* values, ssize size, PxAddressIP address, u16 port);

ssize
pxWin32SocketUDPRead(PxWin32SocketUDP* self, u8* values, ssize size, PxAddressIP* address, u16* port);

PxAddressIP
pxWin32SocketUDPGetAddress(PxWin32SocketUDP* self);

u16
pxWin32SocketUDPGetPort(PxWin32SocketUDP* self);

#endif // PX_WIN32_NETWORK_SOCKET_UDP_H
