#ifndef PX_WIN32_NETWORK_SOCKET_TCP_C
#define PX_WIN32_NETWORK_SOCKET_TCP_C

#include "socket-tcp.h"

PxWin32SocketTCP*
pxWin32SocketTCPReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32SocketTCP);
}

b32
pxWin32SocketTCPCreate(PxWin32SocketTCP* self, PxAddressIP address, u16 port)
{
    PxSockAddrStorage storage = {0};
    ssize             length  = 0;

    if (self == 0 || address.kind == PxAddressIP_None || pxWin32NetworkStart() == 0)
        return 0;

    storage = pxSockAddrStorageMake(address, port, &length);

    SOCKET handle = WSASocketA(storage.ss_family, SOCK_STREAM, IPPROTO_TCP,
        0, 0, WSA_FLAG_OVERLAPPED);

    if (handle == INVALID_SOCKET) return 0;

    self->handle  = handle;
    self->storage = storage;

    return 1;
}

b32
pxWin32SocketTCPAccept(PxWin32SocketTCP* self, PxWin32SocketTCP* value)
{
    if (self == 0 || value == 0 || pxWin32NetworkStart() == 0)
        return 0;

    PxSockAddrStorage storage = {0};
    int               length  = sizeof(PxSockAddrStorage);

    SOCKET handle = accept(self->handle, ((PxSockAddr*) &storage), &length);

    if (handle == INVALID_SOCKET) return 0;

    value->handle  = handle;
    value->storage = storage;

    return 1;
}

void
pxWin32SocketTCPDestroy(PxWin32SocketTCP* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    *self = (PxWin32SocketTCP) {0};

    pxWin32NetworkStop();
}

b32
pxWin32SocketTCPBind(PxWin32SocketTCP* self)
{
    ssize length = 0;

    if (self == 0) return 0;

    switch (self->storage.ss_family) {
        case AF_INET:  length = sizeof(PxSockAddrIn4); break;
        case AF_INET6: length = sizeof(PxSockAddrIn6); break;

        default: break;
    }

    if (length == 0) return 0;

    if (bind(self->handle, ((PxSockAddr*) &self->storage), length) == SOCKET_ERROR)
        return 0;

    return 1;
}

b32
pxWin32SocketTCPBindTo(PxWin32SocketTCP* self, PxAddressIP address, u16 port)
{
    PxSockAddrStorage storage = {0};
    ssize             length  = 0;

    storage = pxSockAddrStorageMake(address, port, &length);

    if (self == 0 || storage.ss_family != self->storage.ss_family) return 0;

    if (bind(self->handle, ((PxSockAddr*) &storage), length) == SOCKET_ERROR)
        return 0;

    self->storage = storage;

    return 1;
}

b32
pxWin32SocketTCPListen(PxWin32SocketTCP* self)
{
    if (self == 0) return 0;

    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    return 1;
}

b32
pxWin32SocketTCPConnect(PxWin32SocketTCP* self, PxAddressIP address, u16 port)
{
    PxSockAddrStorage storage = {0};
    ssize             length  = 0;

    if (self == 0 || port == 0 || address.kind == PxAddressIP_None) return 0;

    storage = pxSockAddrStorageMake(address, port, &length);

    if (connect(self->handle, ((PxSockAddr*) &storage), length) == SOCKET_ERROR)
        return 0;

    return 1;
}

ssize
pxWin32SocketTCPWrite(PxWin32SocketTCP* self, u8* values, ssize size)
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
pxWin32SocketTCPRead(PxWin32SocketTCP* self, u8* values, ssize size)
{
    if (self == 0 || values == 0 || size <= 0) return 0;

    ssize count = recv(self->handle,
        ((char*) values), ((int) size), 0);

    if (count < 0 || count >= size) return 0;

    return count;
}

PxAddressIP
pxWin32SocketTCPGetAddress(PxWin32SocketTCP* self)
{
    return pxSockAddrStorageGetAddress(&self->storage);
}

u16
pxWin32SocketTCPGetPort(PxWin32SocketTCP* self)
{
    return pxSockAddrStorageGetPort(&self->storage);
}

#endif // PX_WIN32_NETWORK_SOCKET_TCP_C
