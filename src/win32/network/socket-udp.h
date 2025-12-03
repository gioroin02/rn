#ifndef RN_WIN32_NETWORK_SOCKET_UDP_H
#define RN_WIN32_NETWORK_SOCKET_UDP_H

#include "./address.h"

#pragma comment(lib, "ws2_32.lib")

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

typedef struct RnWin32SocketUDP
{
    SOCKET            handle;
    RnSockAddrStorage storage;
}
RnWin32SocketUDP;

RnWin32SocketUDP*
rnWin32SocketUDPReserve(RnMemoryArena* arena);

b32
rnWin32SocketUDPCreate(RnWin32SocketUDP* self, RnAddressIPKind kind);

void
rnWin32SocketUDPDestroy(RnWin32SocketUDP* self);

b32
rnWin32SocketUDPBind(RnWin32SocketUDP* self, u16 port);

b32
rnWin32SocketUDPConnect(RnWin32SocketUDP* self, RnAddressIP address, u16 port);

ssize
rnWin32SocketUDPWrite(RnWin32SocketUDP* self, u8* values, ssize size);

ssize
rnWin32SocketUDPWriteHost(RnWin32SocketUDP* self, u8* values, ssize size, RnAddressIP address, u16 port);

ssize
rnWin32SocketUDPRead(RnWin32SocketUDP* self, u8* values, ssize size);

ssize
rnWin32SocketUDPReadHost(RnWin32SocketUDP* self, u8* values, ssize size, RnAddressIP* address, u16* port);

#endif // RN_WIN32_NETWORK_SOCKET_UDP_H
