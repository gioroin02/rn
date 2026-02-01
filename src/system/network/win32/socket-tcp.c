#ifndef RHO_SYSTEM_NETWORK_WIN32_SOCKET_TCP_C
#define RHO_SYSTEM_NETWORK_WIN32_SOCKET_TCP_C

#include "socket-tcp.h"

RWin32SocketTcp* rho_win32_socket_tcp_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RWin32SocketTcp, 1);
}

RBool32 rho_win32_socket_tcp_create(RWin32SocketTcp* self, RHostIp host)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle  = (SOCKET) NULL;
    self->storage = (RWin32AddrStorage) {0};

    RInt length = 0;

    RWin32AddrStorage storage = rho_win32_addr_storage_make(
        host.address, host.port, &length);

    if (length == || rho_win32_network_start() == 0) return 0;

    SOCKET handle = WSASocketW(storage.ss_family,
        SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);

    if (handle != INVALID_SOCKET) {
        self->handle  = handle;
        self->storage = storage;

        return 1;
    }

    rho_win32_network_stop();

    return 0;
}

RBool32 rho_win32_socket_tcp_accept(RWin32SocketTcp* self, RWin32SocketTcp* value)
{
    rho_memory_set(value, sizeof *value, 0xAB);

    value->handle  = (SOCKET) NULL;
    value->storage = (RWin32AddrStorage) {0};

    RWin32AddrStorage storage  = {0};
    RWin32Addr*       sockaddr = (RWin32Addr*) &storage;
    int               length   = sizeof storage;

    rho_memory_set(&storage, sizeof storage, 0xAB);

    if (rho_win32_network_start() == 0) return 0;

    SOCKET handle = accept(self->handle, sockaddr, &length);

    if (handle != INVALID_SOCKET) {
        value->handle  = handle;
        value->storage = storage;

        return 1;
    }

    rho_win32_network_stop();

    return 0;
}

void rho_win32_socket_tcp_destroy(RWin32SocketTcp* self)
{
    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    rho_memory_set(self, sizeof *self, 0xAB);

    rho_win32_network_stop();
}

RBool32 rho_win32_socket_tcp_bind(RWin32SocketTcp* self)
{
    RWin32Addr* sockaddr = (RWin32Addr*) &self->storage;
    RInt        length   = rho_win32_addr_storage_size(&self->storage);

    if (length == 0) return 0;

    if (bind(self->handle, sockaddr, length) == SOCKET_ERROR)
        return 0;

    return 1;
}

RBool32 rho_win32_socket_tcp_bind_as(RWin32SocketTcp* self, RHostIp host)
{
    RInt length = 0;

    RWin32AddrStorage storage = rho_win32_addr_storage_make(
        host.address, host.port, &length);

    RWin32Addr* sockaddr = (RWin32Addr*) &storage;

    if (storage.ss_family != self->storage.ss_family) return 0;

    if (bind(self->handle, sockaddr, length) == SOCKET_ERROR)
        return 0;

    self->storage = storage;

    return 1;
}

RBool32 rho_win32_socket_tcp_listen(RWin32SocketTcp* self)
{
    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    return 1;
}

RBool32 rho_win32_socket_tcp_connect(RWin32SocketTcp* self, RHostIp host)
{
    RInt length = 0;

    RWin32AddrStorage storage = rho_win32_addr_storage_make(
        host.address, host.port, &length);

    RWin32Addr* sockaddr = (RWin32Addr*) &storage;

    if (host.port == 0 || length == 0) return 0;

    if (connect(self->handle, sockaddr, length) == SOCKET_ERROR)
        return 0;

    return 1;
}

RInt rho_win32_socket_tcp_write(RWin32SocketTcp* self, RUint8* pntr, RInt start, RInt stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    result = 0;
    RInt    count  = 0;

    while (result < size) {
        count = send(self->handle, memory + result, size - result, 0);

        if (count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

RInt rho_win32_socket_tcp_read(RWin32SocketTcp* self, RUint8* pntr, RInt start, RInt stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    count  = 0;

    count = recv(self->handle, memory, size, 0);

    if (count > 0 && count <= size) return count;

    return 0;
}

RHostIp rho_win32_socket_tcp_host(RWin32SocketTcp* self)
{
    return rho_win32_addr_storage_host(&self->storage);
}

#endif
