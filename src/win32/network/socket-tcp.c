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
    SOCKET          handle;
    RnAddressIPKind kind;
};

RnWin32SocketTCP*
rnWin32SocketTCPReserve(RnMemoryArena* arena)
{
    return rnMemoryArenaReserveOneOf(arena, RnWin32SocketTCP);
}

b32
rnWin32SocketTCPCreate(RnWin32SocketTCP* self, RnAddressIPKind kind)
{
    if (self == 0 || kind == RnAddressIP_None) return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMakeAny(kind, 0, 0);

    SOCKET handle = socket(storage.ss_family, SOCK_STREAM, 0);

    if (handle == INVALID_SOCKET) return 0;

    self->handle = handle;
    self->kind   = kind;

    return 1;
}

b32
rnWin32SocketTCPAccept(RnWin32SocketTCP* self, RnWin32SocketTCP* value)
{
    if (self == 0 || value == 0) return 0;

    int type = sizeof(RnSockAddrStorage);

    RnSockAddrStorage storage = {0};

    SOCKET handle = accept(self->handle, ((RnSockAddr*) &storage), &type);

    if (handle == INVALID_SOCKET) return 0;

    value->handle = handle;
    value->kind   = rnSockAddrStorageGetAddress(&storage).kind;

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
rnWin32SocketTCPListen(RnWin32SocketTCP* self, u16 port)
{
    if (self == 0 || port <= 0) return 0;

    ssize type = 0;

    RnSockAddrStorage storage = rnSockAddrStorageMakeAny(self->kind, port, &type);

    if (bind(self->handle, ((RnSockAddr*) &storage), type) == SOCKET_ERROR)
        return 0;

    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR) return 0;

    return 1;
}

b32
rnWin32SocketTCPConnect(RnWin32SocketTCP* self, RnAddressIP address, u16 port)
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
rnWin32SocketTCPWrite(RnWin32SocketTCP* self, u8* values, ssize size)
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
rnWin32SocketTCPRead(RnWin32SocketTCP* self, u8* values, ssize size)
{
    if (self == 0 || values == 0 || size <= 0) return 0;

    ssize count = recv(self->handle,
        ((char*) values), ((int) size), 0);

    if (count < 0 || count >= size) return 0;

    return count;
}

#endif // RN_WIN32_NETWORK_SOCKET_TCP_C
