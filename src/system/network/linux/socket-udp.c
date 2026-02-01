#ifndef RHO_SYSTEM_NETWORK_LINUX_SOCKET_UDP_C
#define RHO_SYSTEM_NETWORK_LINUX_SOCKET_UDP_C

#include "socket-udp.h"

RLinuxSocketUdp* rho_linux_socket_udp_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RLinuxSocketUdp, 1);
}

RBool32 rho_linux_socket_udp_create(RLinuxSocketUdp* self, RHostIp host)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle = -1;
    self->storage = (RLinuxAddrStorage) {0};

    RInt length  = 0;
    int  option  = 1;
    int  status  = 0;

    RLinuxAddrStorage storage = rho_linux_addr_storage_make(
        host.address, host.port, &length);

    if (length == 0) return 0;

    RInt handle = socket(storage.ss_family,
        SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);

    if (handle != -1) {
        do {
            status = setsockopt(handle, SOL_SOCKET,
                SO_REUSEADDR, &option, sizeof option);
        }
        while (status == -1 && errno == EINTR);

        if (status != -1) {
            self->handle  = handle;
            self->storage = storage;

            return 1;
        }
    }

    do {
        status = close(handle);
    }
    while (status == -1 && errno == EINTR);

    return 0;
}

void rho_linux_socket_udp_destroy(RLinuxSocketUdp* self)
{
    int status = 0;

    if (self->handle == -1) return;

    do {
        status = close(self->handle);
    }
    while (status == -1 && errno == EINTR);

    rho_memory_set(self, sizeof *self, 0xAB);
}

RBool32 rho_linux_socket_udp_bind(RLinuxSocketUdp* self)
{
    RLinuxAddr* sockaddr = (RLinuxAddr*) &self->storage;
    RInt        length   = rho_linux_addr_storage_size(&self->storage);
    int         status   = 0;

    if (length == 0) return 0;

    do {
        status = bind(self->handle, sockaddr, length);
    }
    while (status == -1 && errno == EINTR);

    if (status == -1) return 0;

    return 1;
}

RBool32 rho_linux_socket_udp_bind_as(RLinuxSocketUdp* self, RHostIp host)
{
    RInt length = 0;
    int  status = 0;

    RLinuxAddrStorage storage = rho_linux_addr_storage_make(
        host.address, host.port, &length);

    RLinuxAddr* sockaddr = (RLinuxAddr*) &storage;

    if (storage.ss_family != self->storage.ss_family)
        return 0;

    do {
        status = bind(self->handle, sockaddr, length);
    }
    while (status == -1 && errno == EINTR);

    if (status == -1) return 0;

    self->storage = storage;

    return 1;
}

RInt rho_linux_socket_udp_write(RLinuxSocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp host)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    result = 0;
    RInt    count  = 0;
    RInt    length = 0;

    RLinuxAddrStorage storage = rho_linux_addr_storage_make(
        host.address, host.port, &length);

    RLinuxAddr* sockaddr = (RLinuxAddr*) &storage;

    while (result < size) {
        do {
            count = sendto(self->handle, memory + result,
                size - result, 0, sockaddr, length);
        }
        while (count == -1 && errno == EINTR);

        if (count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

RInt rho_linux_socket_udp_read(RLinuxSocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp* host)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    count  = 0;

    RLinuxAddrStorage storage  = {0};
    RLinuxAddr*       sockaddr = (RLinuxAddr*) &storage;
    socklen_t         length   = sizeof storage;

    rho_memory_set(&storage, sizeof storage, 0xAB);

    do {
        count = recvfrom(self->handle, memory, size, 0, sockaddr, &length);
    }
    while (count == -1 && errno == EINTR);

    if (count > 0 && count <= size && length > 0) {
        if (host != NULL)
            *host = rho_linux_addr_storage_host(&storage);

        return count;
    }

    return 0;
}

RHostIp rho_linux_socket_udp_host(RLinuxSocketUdp* self)
{
    return rho_linux_addr_storage_host(&self->storage);
}

#endif
