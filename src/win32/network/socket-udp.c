#ifndef PX_WIN32_NETWORK_SOCKET_UDP_C
#define PX_WIN32_NETWORK_SOCKET_UDP_C

#include "socket-udp.h"

PxWin32SocketUDP*
pxWin32SocketUDPReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32SocketUDP);
}

b32
pxWin32SocketUDPCreate(PxWin32SocketUDP* self, PxAddressIP address, u16 port)
{
    PxSockAddrStorage storage = {0};
    ssize             length  = 0;

    if (self == 0 || address.kind == PxAddressIP_None || pxWin32NetworkStart() == 0)
        return 0;

    storage = pxSockAddrStorageMake(address, port, &length);

    SOCKET handle = WSASocketA(storage.ss_family, SOCK_DGRAM, IPPROTO_UDP,
        0, 0, WSA_FLAG_OVERLAPPED);

    if (handle == INVALID_SOCKET) return 0;

    self->handle  = handle;
    self->storage = storage;

    return 1;
}

void
pxWin32SocketUDPDestroy(PxWin32SocketUDP* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    *self = (PxWin32SocketUDP) {0};

    pxWin32NetworkStop();
}

b32
pxWin32SocketUDPBind(PxWin32SocketUDP* self)
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
pxWin32SocketUDPBindTo(PxWin32SocketUDP* self, PxAddressIP address, u16 port)
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

ssize
pxWin32SocketUDPWrite(PxWin32SocketUDP* self, u8* values, ssize size, PxAddressIP address, u16 port)
{
    if (self == 0 || values == 0 || size <= 0) return 0;

    ssize length = 0;
    ssize count  = 0;

    PxSockAddrStorage storage = pxSockAddrStorageMake(address, port, &length);

    for (ssize temp = 0; count < size; count += temp) {
        temp = sendto(self->handle, ((char*) values + count),
            ((int) size - count), 0, ((PxSockAddr*) &storage), length);

        if (temp <= 0 || temp > size - count) break;
    }

    return count;
}

ssize
pxWin32SocketUDPRead(PxWin32SocketUDP* self, u8* values, ssize size, PxAddressIP* address, u16* port)
{
    if (self == 0 || values == 0 || size <= 0) return 0;

    int   length = sizeof(PxSockAddrStorage);
    ssize count  = 0;

    PxSockAddrStorage storage = {0};

    count = recvfrom(self->handle, ((char*) values), ((int) size),
        0, ((PxSockAddr*) &storage), &length);

    if (count <= 0 || count > size) return 0;

    if (address != 0) *address = pxSockAddrStorageGetAddress(&storage);
    if (port != 0)    *port    = pxSockAddrStorageGetPort(&storage);

    return count;
}

PxAddressIP
pxWin32SocketUDPGetAddress(PxWin32SocketUDP* self)
{
    return pxSockAddrStorageGetAddress(&self->storage);
}

u16
pxWin32SocketUDPGetPort(PxWin32SocketUDP* self)
{
    return pxSockAddrStorageGetPort(&self->storage);
}

#endif // PX_WIN32_NETWORK_SOCKET_UDP_C
