#ifndef RN_WIN32_NETWORK_SOCKET_TCP_C
#define RN_WIN32_NETWORK_SOCKET_TCP_C

#pragma comment(lib, "Ws2_32.lib")

#include "./socket-tcp.h"
#include "./address.c"

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

struct RnWin32SocketTCP
{
    SOCKET handle;

    RnAddressIPKind kind;
    u16             port;
};

RnWin32SocketTCP*
rnWin32SocketTCPReserve(RnMemoryArena* arena)
{
    return rnMemoryArenaReserveType(arena, RnWin32SocketTCP);
}

b32
rnWin32SocketTCPCreate(RnWin32SocketTCP* self, RnAddressIPKind kind)
{
    if (self == 0 || self->port != 0 || kind == RnAddressIP_None)
        return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMakeEmpty(kind);

    SOCKET handle = WSASocket(storage.ss_family,
        SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);

    if (handle == INVALID_SOCKET) return 0;

    self->handle = handle;
    self->kind   = kind;

    return 1;
}

b32
rnWin32SocketTCPAccept(RnWin32SocketTCP* self, RnWin32SocketTCP* value)
{
    int size = sizeof(RnSockAddrStorage);

    if (self == 0 || self->port == 0 || value == 0 || value->port != 0)
        return 0;

    RnSockAddrStorage storage = {0};
    RnWin32SocketTCP  temp    = {0};

    temp.handle = accept(
        self->handle, ((RnSockAddr*) &storage), &size);

    if (temp.handle == INVALID_SOCKET) return 0;

    temp.kind = rnSockAddrStorageGetAddress(&storage).kind;
    temp.port = rnSockAddrStorageGetPort(&storage);

    *value = temp;

    return 1;
}

void
rnWin32SocketTCPDestroy(RnWin32SocketTCP* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    *self = (RnWin32SocketTCP) {0};
}

b32
rnWin32SocketTCPBind(RnWin32SocketTCP* self, RnAddressIP address, u16 port)
{
    ssize size = 0;

    if (self == 0 || self->port != 0 || port == 0) return 0;

    if (self->kind != address.kind) return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMake(address, port, &size);

    if (bind(self->handle, ((RnSockAddr*) &storage), size) == SOCKET_ERROR)
        return 0;

    self->port = port;

    return 1;
}

b32
rnWin32SocketTCPListen(RnWin32SocketTCP* self, u16 port, ssize max)
{
    ssize size = 0;

    if (self == 0 || self->port != 0 || port == 0) return 0;

    RnAddressIP       address = rnAddressIPEmpty(self->kind);
    RnSockAddrStorage storage = rnSockAddrStorageMake(address, port, &size);

    if (bind(self->handle, ((RnSockAddr*) &storage), size) == SOCKET_ERROR)
        return 0;

    if (listen(self->handle, rnClamp(max, 0, SOMAXCONN)) == SOCKET_ERROR)
        return 0;

    self->port = port;

    return 1;
}

b32
rnWin32SocketTCPConnect(RnWin32SocketTCP* self, RnAddressIP address, u16 port)
{
    ssize size = 0;

    if (self == 0 || port == 0 || address.kind == RnAddressIP_None)
        return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMake(address, port, &size);

    if (connect(self->handle, ((RnSockAddr*) &storage), size) == SOCKET_ERROR)
        return 0;

    return 1;
}

ssize
rnWin32SocketTCPWrite(RnWin32SocketTCP* self, u8* values, ssize size)
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
rnWin32SocketTCPRead(RnWin32SocketTCP* self, u8* values, ssize size)
{
    ssize count = recv(self->handle,
        ((char*) values), ((int) size), 0);

    if (count < 0 || count >= size)
        return 0;

    return count;
}

#endif // RN_WIN32_NETWORK_SOCKET_TCP_C
