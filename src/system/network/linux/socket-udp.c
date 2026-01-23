#ifndef P_SYSTEM_LINUX_NETWORK_SOCKET_UDP_C
#define P_SYSTEM_LINUX_NETWORK_SOCKET_UDP_C

#include "socket-udp.h"

PLinuxSocketUdp* pLinuxSocketUdpReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PLinuxSocketUdp);
}

Bool pLinuxSocketUdpCreate(PLinuxSocketUdp* self, PHostIp host)
{
    pMemorySet(self, sizeof *self, 0xAB);

    PLinuxAddrStorage storage;
    Int               length = 0;

    storage = pLinuxAddrStorageMake(host.address, host.port, &length);

    if (length == 0) return 0;

    Int handle = socket(storage.ss_family, SOCK_DGRAM, IPPROTO_UDP);

    if (handle != -1) {
        self->handle  = handle;
        self->storage = storage;

        return 1;
    }

    return 0;
}

void pLinuxSocketUdpDestroy(PLinuxSocketUdp* self)
{
    int status = 0;

    if (self->handle == -1) return;

    do {
        status = close(self->handle);
    }
    while (status == -1 && errno == EINTR);

    pMemorySet(self, sizeof *self, 0xAB);
}

Bool pLinuxSocketUdpBind(PLinuxSocketUdp* self)
{
    PLinuxAddr* sockaddr = (PLinuxAddr*) &self->storage;
    Int         length   = pLinuxAddrStorageGetSize(&self->storage);

    if (length == 0) return 0;

    if (bind(self->handle, sockaddr, length) == -1)
        return 0;

    return 1;
}

Bool pLinuxSocketUdpBindAs(PLinuxSocketUdp* self, PHostIp host)
{
    PLinuxAddrStorage storage;
    PLinuxAddr*       sockaddr = (PLinuxAddr*) &storage;
    Int               length   = 0;

    storage = pLinuxAddrStorageMake(host.address, host.port, &length);

    if (storage.ss_family != self->storage.ss_family) return 0;

    if (bind(self->handle, sockaddr, length) == -1)
        return 0;

    self->storage = storage;

    return 1;
}

Int pLinuxSocketUdpWrite(PLinuxSocketUdp* self, U8* pntr, Int start, Int stop, PHostIp host)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    PLinuxAddrStorage storage;
    PLinuxAddr*       sockaddr = (PLinuxAddr*) &storage;
    Int               length   = 0;

    storage = pLinuxAddrStorageMake(host.address, host.port, &length);

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int result = 0;

    while (result < size) {
        Int count = sendto(self->handle, memory + result,
            size - result, 0, sockaddr, length);

        if (count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

Int pLinuxSocketUdpRead(PLinuxSocketUdp* self, U8* pntr, Int start, Int stop, PHostIp* host)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    PLinuxAddrStorage storage;
    PLinuxAddr*       sockaddr = (PLinuxAddr*) &storage;
    int               length   = sizeof storage;

    pMemorySet(&storage, sizeof storage, 0xAB);

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int count  = recvfrom(self->handle, memory, size, 0, sockaddr, &length);

    if (count > 0 && count <= size && length > 0) {
        if (host != NULL) {
            *host = pHostIpMake(
                pLinuxAddrStorageGetAddress(&storage),
                pLinuxAddrStorageGetPort(&storage));
        }

        return count;
    }

    return 0;
}

PHostIp pLinuxSocketUdpGetHost(PLinuxSocketUdp* self)
{
    return pHostIpMake(
        pLinuxAddrStorageGetAddress(&self->storage),
        pLinuxAddrStorageGetPort(&self->storage));
}

#endif // P_SYSTEM_LINUX_NETWORK_SOCKET_UDP_C
