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
    b32             bound;
};

RnWin32SocketUDP*
rnWin32SocketUDPReserve(RnMemoryArena* arena)
{
    return rnMemoryArenaReserveOneOf(arena, RnWin32SocketUDP);
}

b32
rnWin32SocketUDPCreate(RnWin32SocketUDP* self, RnAddressIPKind kind)
{
    if (self == 0 || self->bound != 0 || kind == RnAddressIP_None)
        return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMakeEmpty(kind);

    SOCKET handle = WSASocket(storage.ss_family,
        SOCK_DGRAM, IPPROTO_UDP, 0, 0, WSA_FLAG_OVERLAPPED);

    if (handle == INVALID_SOCKET) return 0;

    self->handle = handle;
    self->kind   = kind;

    return 1;
}

b32
rnWin32SocketUDPAccept(RnWin32SocketUDP* self, RnWin32SocketUDP* value)
{
    int type = sizeof(RnSockAddrStorage);

    if (self == 0 || self->bound == 0 || value == 0 || value->bound != 0)
        return 0;

    RnSockAddrStorage storage = {0};
    RnWin32SocketUDP  temp    = {0};

    temp.handle = accept(self->handle, ((RnSockAddr*) &storage), &type);

    if (temp.handle == INVALID_SOCKET) return 0;

    temp.kind  = rnSockAddrStorageGetAddress(&storage).kind;
    temp.bound = 1;

    *value = temp;

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
rnWin32SocketUDPBind(RnWin32SocketUDP* self, RnAddressIP address, u16 port)
{
    ssize type = 0;

    if (self == 0 || self->bound != 0 || self->kind != address.kind)
        return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMake(address, port, &type);

    if (bind(self->handle, ((RnSockAddr*) &storage), type) == SOCKET_ERROR)
        return 0;

    self->bound = 1;

    return 1;
}

b32
rnWin32SocketUDPListen(RnWin32SocketUDP* self)
{
    if (self == 0) return 0;

    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    return 1;
}

b32
rnWin32SocketUDPConnect(RnWin32SocketUDP* self, RnAddressIP address, u16 port)
{
    ssize type = 0;

    if (self == 0 || port == 0 || address.kind == RnAddressIP_None)
        return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMake(address, port, &type);

    if (connect(self->handle, ((RnSockAddr*) &storage), type) == SOCKET_ERROR)
        return 0;

    return 1;
}

ssize
rnWin32SocketUDPWrite(RnWin32SocketUDP* self, u8* values, ssize size)
{
    ssize count = 0;

    while (count < size) {
        ssize temp = send(self->handle, ((char*) values + count),
            ((int) size - count), 0);

        if (temp <= 0 || temp > size - count)
            break;

        count += temp;
    }

    return count;
}

ssize
rnWin32SocketUDPWriteHost(RnWin32SocketUDP* self, u8* values, ssize size, RnAddressIP address, u16 port)
{
    ssize type  = 0;
    ssize count = 0;

    RnSockAddrStorage storage = rnSockAddrStorageMake(address, port, &type);

    while (count < size) {
        ssize temp = sendto(self->handle, ((char*) values + count),
            ((int) size - count), 0, ((RnSockAddr*) &storage), type);

        if (temp <= 0 || temp > size - count)
            break;

        count += temp;
    }

    return count;
}

ssize
rnWin32SocketUDPRead(RnWin32SocketUDP* self, u8* values, ssize size)
{
    ssize count = recv(self->handle,
        ((char*) values), ((int) size), 0);

    if (count < 0 || count >= size)
        return 0;

    return count;
}

ssize
rnWin32SocketUDPReadHost(RnWin32SocketUDP* self, u8* values, ssize size, RnAddressIP* address, u16* port)
{
    int   type  = 0;
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
