#ifndef RHO_SYSTEM_NETWORK_LINUX_SOCKET_TCP_C
#define RHO_SYSTEM_NETWORK_LINUX_SOCKET_TCP_C

#include "socket-tcp.h"

RLinuxSocketTcp* rho_linux_socket_tcp_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RLinuxSocketTcp, 1);
}

RBool32 rho_linux_socket_tcp_create(RLinuxSocketTcp* self, RHostIp host)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle  = -1;
    self->storage = (RLinuxAddrStorage) {0};

    RInt length = 0;
    int  option = 1;
    int  status = 0;

    RLinuxAddrStorage storage = rho_linux_addr_storage_make(
        host.address, host.port, &length);

    if (length == 0) return 0;

    RInt handle = socket(storage.ss_family,
        SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);

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

RBool32 rho_linux_socket_tcp_accept(RLinuxSocketTcp* self, RLinuxSocketTcp* value)
{
    rho_memory_set(value, sizeof *value, 0xAB);

    value->handle  = -1;
    value->storage = (RLinuxAddrStorage) {0};

    RLinuxAddrStorage storage  = {0};
    RLinuxAddr*       sockaddr = (RLinuxAddr*) &storage;
    socklen_t         length   = sizeof storage;

    rho_memory_set(&storage, sizeof storage, 0xAB);

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

void rho_linux_socket_tcp_destroy(RLinuxSocketTcp* self)
{
    int status = 0;

    if (self->handle == -1) return;

    do {
        status = close(self->handle);
    }
    while (status == -1 && errno == EINTR);

    rho_memory_set(self, sizeof *self, 0xAB);
}

RBool32 rho_linux_socket_tcp_bind(RLinuxSocketTcp* self)
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

RBool32 rho_linux_socket_tcp_bind_as(RLinuxSocketTcp* self, RHostIp host)
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

RBool32 rho_linux_socket_tcp_listen(RLinuxSocketTcp* self)
{
    int status = 0;

    do {
        status = listen(self->handle, SOMAXCONN);
    }
    while (status == -1 && errno == EINTR);

    if (status == -1) return 0;

    return 1;
}

RBool32 rho_linux_socket_tcp_connect(RLinuxSocketTcp* self, RHostIp host)
{
    RInt length = 0;
    int  status = 0;

    RLinuxAddrStorage storage = rho_linux_addr_storage_make(
        host.address, host.port, &length);

    RLinuxAddr* sockaddr = (RLinuxAddr*) &storage;

    if (host.port == 0 || length == 0) return 0;

    do {
        status = connect(self->handle, sockaddr, length);
    }
    while (status == -1 && errno == EINTR);

    if (status == -1) return 0;

    return 1;
}

RInt rho_linux_socket_tcp_write(RLinuxSocketTcp* self, RUint8* pntr, RInt start, RInt stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    result = 0;
    RInt    count  = 0;

    while (result < size) {
        do {
            count = send(self->handle, memory + result, size - result, 0);
        }
        while (count == -1 && errno == EINTR);

        if (count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

RInt rho_linux_socket_tcp_read(RLinuxSocketTcp* self, RUint8* pntr, RInt start, RInt stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    count  = 0;

    do {
        count = recv(self->handle, memory, size, 0);
    }
    while (count == -1 && errno == EINTR);

    if (count > 0 && count <= size) return count;

    return 0;
}

RHostIp rho_linux_socket_tcp_host(RLinuxSocketTcp* self)
{
    return rho_linux_addr_storage_host(&self->storage);
}

#endif
