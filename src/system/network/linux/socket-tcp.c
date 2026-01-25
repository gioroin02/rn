#ifndef P_SYSTEM_LINUX_NETWORK_SOCKET_TCP_C
#define P_SYSTEM_LINUX_NETWORK_SOCKET_TCP_C

#include "socket-tcp.h"

PLinuxSocketTcp* pLinuxSocketTcpReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PLinuxSocketTcp);
}

B32 pLinuxSocketTcpCreate(PLinuxSocketTcp* self, PHostIp host)
{
    pMemorySet(self, sizeof *self, 0xAB);

    PLinuxAddrStorage storage;
    Int               length = 0;
    int               option = 1;

    storage = pLinuxAddrStorageMake(host.address, host.port, &length);

    if (length == 0) return 0;

    Int handle = socket(storage.ss_family, SOCK_STREAM, IPPROTO_TCP);

    if (handle != -1) {
        int status = setsockopt(handle, SOL_SOCKET,
            SO_REUSEADDR, &option, sizeof option);

        if (status != -1) {
            self->handle  = handle;
            self->storage = storage;

            return 1;
        }
    }

    close(handle);

    return 0;
}

B32 pLinuxSocketTcpAccept(PLinuxSocketTcp* self, PLinuxSocketTcp* value)
{
    pMemorySet(value, sizeof *value, 0xAB);

    PLinuxAddrStorage storage;
    PLinuxAddr*       sockaddr = (PLinuxAddr*) &storage;
    int               length   = sizeof storage;

    pMemorySet(&storage, sizeof storage, 0xAB);

    int handle = -1;

    do {
        handle = accept(self->handle, sockaddr, &length);
    }
    while (handle == -1 && errno == EINTR);

    if (handle != -1) {
        value->handle  = handle;
        value->storage = storage;

        return 1;
    }

    return 0;
}

void pLinuxSocketTcpDestroy(PLinuxSocketTcp* self)
{
    int status = 0;

    if (self->handle == -1) return;

    do {
        status = close(self->handle);
    }
    while (status == -1 && errno == EINTR);

    pMemorySet(self, sizeof *self, 0xAB);
}

B32 pLinuxSocketTcpBind(PLinuxSocketTcp* self)
{
    PLinuxAddr* sockaddr = (PLinuxAddr*) &self->storage;
    Int         length   = pLinuxAddrStorageGetSize(&self->storage);

    if (length == 0) return 0;

    if (bind(self->handle, sockaddr, length) == -1)
        return 0;

    return 1;
}

B32 pLinuxSocketTcpBindAs(PLinuxSocketTcp* self, PHostIp host)
{
    PLinuxAddrStorage storage;
    PLinuxAddr*       sockaddr = (PLinuxAddr*) &self->storage;
    Int               length   = 0;

    storage = pLinuxAddrStorageMake(host.address, host.port, &length);

    if (storage.ss_family != self->storage.ss_family) return 0;

    if (bind(self->handle, sockaddr, length) == -1)
        return 0;

    self->storage = storage;

    return 1;
}

B32 pLinuxSocketTcpListen(PLinuxSocketTcp* self)
{
    if (listen(self->handle, SOMAXCONN) == -1)
        return 0;

    return 1;
}

B32 pLinuxSocketTcpConnect(PLinuxSocketTcp* self, PHostIp host)
{
    PLinuxAddrStorage storage;
    PLinuxAddr*       sockaddr = (PLinuxAddr*) &storage;
    Int               length   = 0;

    storage = pLinuxAddrStorageMake(host.address, host.port, &length);

    if (host.port == 0 || length == 0) return 0;

    if (connect(self->handle, sockaddr, length) == -1)
        return 0;

    return 1;
}

Int pLinuxSocketTcpWrite(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int result = 0;

    while (result < size) {
        Int count = send(self->handle,
            memory + result, size - result, 0);

        if (count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

Int pLinuxSocketTcpRead(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int count  = recv(self->handle, memory, size, 0);

    if (count > 0 && count <= size) return count;

    return 0;
}

PHostIp pLinuxSocketTcpGetHost(PLinuxSocketTcp* self)
{
    return pHostIpMake(
        pLinuxAddrStorageGetAddress(&self->storage),
        pLinuxAddrStorageGetPort(&self->storage));
}

#endif
