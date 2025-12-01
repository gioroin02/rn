#ifndef RN_WIN32_NETWORK_SOCKET_UDP_C
#define RN_WIN32_NETWORK_SOCKET_UDP_C

#pragma comment(lib, "Ws2_32.lib")

#include "./socket-udp.h"
#include "./address.c"

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

struct RnWin32SocketUDP
{
    SOCKET          handle;
    RnAddressIPKind kind;
};

RnWin32SocketUDP*
rnWin32SocketUDPReserve(RnMemoryArena* arena)
{
    return rnMemoryArenaReserveOneOf(arena, RnWin32SocketUDP);
}

b32
rnWin32SocketUDPCreate(RnWin32SocketUDP* self, RnAddressIPKind kind)
{
    if (self == 0 || kind == RnAddressIP_None) return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMakeAny(kind, 0, 0);

    SOCKET handle = socket(storage.ss_family, SOCK_DGRAM, 0);

    if (handle == INVALID_SOCKET) return 0;

    self->handle = handle;
    self->kind   = kind;

    return 1;
}

void
rnWin32SocketUDPDestroy(RnWin32SocketUDP* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    *self = (RnWin32SocketUDP) {0};
}

b32
rnWin32SocketUDPBind(RnWin32SocketUDP* self, u16 port)
{
    if (self == 0 || port <= 0) return 0;

    ssize type = 0;

    RnSockAddrStorage storage = rnSockAddrStorageMakeAny(self->kind, port, &type);

    if (bind(self->handle, ((RnSockAddr*) &storage), type) == SOCKET_ERROR)
        return 0;

    return 1;
}

b32
rnWin32SocketUDPConnect(RnWin32SocketUDP* self, RnAddressIP address, u16 port)
{
    if (self == 0 || port == 0 || address.kind == RnAddressIP_None)
        return 0;

    ssize type = 0;

    RnSockAddrStorage storage = rnSockAddrStorageMake(address, port, &type);

    if (connect(self->handle, ((RnSockAddr*) &storage), type) == SOCKET_ERROR)
        return 0;

    return 1;
}

ssize
rnWin32SocketUDPWrite(RnWin32SocketUDP* self, u8* values, ssize size)
{
    if (self == 0 || values == 0 || size <= 0) return 0;

    ssize count = 0;

    for (ssize temp = 0; count < size; count += temp) {
        temp = send(self->handle, ((char*) values + count),
            ((int) size - count), 0);

        if (temp <= 0 || temp > size - count) break;
    }

    return count;
}

ssize
rnWin32SocketUDPWriteHost(RnWin32SocketUDP* self, u8* values, ssize size, RnAddressIP address, u16 port)
{
    if (self == 0 || values == 0 || size <= 0) return 0;

    ssize type  = 0;
    ssize count = 0;

    RnSockAddrStorage storage = rnSockAddrStorageMake(address, port, &type);

    for (ssize temp = 0; count < size; count += temp) {
        temp = sendto(self->handle, ((char*) values + count),
            ((int) size - count), 0, ((RnSockAddr*) &storage), type);

        if (temp <= 0 || temp > size - count) break;
    }

    return count;
}

ssize
rnWin32SocketUDPRead(RnWin32SocketUDP* self, u8* values, ssize size)
{
    if (self == 0 || values == 0 || size <= 0) return 0;

    ssize count = recv(self->handle,
        ((char*) values), ((int) size), 0);

    if (count < 0 || count >= size) return 0;

    return count;
}

ssize
rnWin32SocketUDPReadHost(RnWin32SocketUDP* self, u8* values, ssize size, RnAddressIP* address, u16* port)
{
    if (self == 0 || values == 0 || size <= 0) return 0;

    int   type  = sizeof(RnSockAddrStorage);
    ssize count = 0;

    RnSockAddrStorage storage = {0};

    count = recvfrom(self->handle, ((char*) values),
        ((int) size), 0, ((RnSockAddr*) &storage), &type);

    if (count <= 0 || count > size) return 0;

    if (address != 0)
        *address = rnSockAddrStorageGetAddress(&storage);

    if (port != 0)
        *port = rnSockAddrStorageGetPort(&storage);

    return count;
}

#endif // RN_WIN32_NETWORK_SOCKET_UDP_C
