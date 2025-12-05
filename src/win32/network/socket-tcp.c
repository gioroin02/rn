#ifndef RN_WIN32_NETWORK_SOCKET_TCP_C
#define RN_WIN32_NETWORK_SOCKET_TCP_C

#include "./socket-tcp.h"

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

    SOCKET handle = WSASocketA(storage.ss_family,
        SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);

    if (handle == INVALID_SOCKET) return 0;

    self->handle  = handle;
    self->storage = storage;

    return 1;
}

b32
rnWin32SocketTCPAccept(RnWin32SocketTCP* self, RnWin32SocketTCP* value)
{
    if (self == 0 || value == 0) return 0;

    int type = sizeof(RnSockAddrStorage);

    RnSockAddrStorage storage = {0};

    SOCKET handle = accept(self->handle,
        ((RnSockAddr*) &storage), &type);

    if (handle == INVALID_SOCKET) return 0;

    value->handle  = handle;
    value->storage = storage;

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
rnWin32SocketTCPBind(RnWin32SocketTCP* self, u16 port)
{
    if (self == 0 || port < 0) return 0;

    RnAddressIPKind kind = RnAddressIP_None;
    ssize           type = 0;

    switch (self->storage.ss_family) {
        case AF_INET:  kind = RnAddressIP_IPv4; break;
        case AF_INET6: kind = RnAddressIP_IPv6; break;

        default: break;
    }

    if (kind == RnAddressIP_None) return 0;

    RnSockAddrStorage storage = rnSockAddrStorageMakeAny(kind, port, &type);

    if (bind(self->handle, ((RnSockAddr*) &storage), type) == SOCKET_ERROR)
        return 0;

    return 1;
}

b32
rnWin32SocketTCPListen(RnWin32SocketTCP* self)
{
    if (self == 0) return 0;

    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

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
