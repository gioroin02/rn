#ifndef RHO_SYSTEM_NETWORK_WIN32_SOCKET_UDP_C
#define RHO_SYSTEM_NETWORK_WIN32_SOCKET_UDP_C

#include "socket-udp.h"

RWin32SocketUdp* rho_win32_socket_udp_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RWin32SocketUdp, 1);
}

RBool32 rho_win32_socket_udp_create(RWin32SocketUdp* self, RHostIp host)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle  = (SOCKET) NULL;
    self->storage = (RWin32AddrStorage) {0};

    RInt length = 0;

    RWin32AddrStorage storage = rho_win32_addr_storage_make(
        host.address, host.port, &length);

    if (length == 0 || rho_win32_network_start() == 0) return 0;

    SOCKET handle = WSASocketW(storage.ss_family,
        SOCK_DGRAM, IPPROTO_UDP, 0, 0, WSA_FLAG_OVERLAPPED);

    if (handle != INVALID_SOCKET) {
        self->handle  = handle;
        self->storage = storage;

        return 1;
    }

    rho_win32_network_stop();

    return 0;
}

void rho_win32_socket_udp_destroy(RWin32SocketUdp* self)
{
    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    rho_memory_set(self, sizeof *self, 0xAB);

    rho_win32_network_stop();
}

RBool32 rho_win32_socket_udp_bind(RWin32SocketUdp* self)
{
    RWin32Addr* sockaddr = (RWin32Addr*) &self->storage;
    RInt        length   = rho_win32_addr_storage_size(&self->storage);

    if (length == 0) return 0;

    if (bind(self->handle, sockaddr, length) == SOCKET_ERROR)
        return 0;

    return 1;
}

RBool32 rho_win32_socket_udp_bind_as(RWin32SocketUdp* self, RHostIp host)
{
    RInt length = 0;

    RWin32AddrStorage storage = rho_win32_addr_storage_make(
        host.address, host.port, &length);

    RWin32Addr* sockaddr = (RWin32Addr*) &storage;

    if (storage.ss_family != self->storage.ss_family)
        return 0;

    if (bind(self->handle, sockaddr, length) == SOCKET_ERROR)
        return 0;

    self->storage = storage;

    return 1;
}

RInt rho_win32_socket_udp_write(RWin32SocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp host)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    result = 0;
    RInt    count  = 0;
    RInt    length = 0;

    RWin32AddrStorage storage = rho_win32_addr_storage_make(
        host.address, host.port, &length);

    RWin32Addr* sockaddr = (RWin32Addr*) &storage;

    while (result < size) {
        count = sendto(self->handle, memory + result,
            size - result, 0, sockaddr, length);

        if (count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

RInt rho_win32_socket_udp_read(RWin32SocketUdp* self, RUint8* pntr, RInt start, RInt stop, RHostIp* host)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    count  = 0;

    RWin32AddrStorage storage  = {0};
    RWin32Addr*       sockaddr = (RWin32Addr*) &storage;
    int               length   = sizeof storage;

    rho_memory_set(&storage, sizeof storage, 0xAB);

    count = recvfrom(self->handle, memory, size, 0, sockaddr, &length);

    if (count > 0 && count <= size && length > 0) {
        if (host != NULL)
            *host = rho_wn32_addr_storage_host(&storage);

        return count;
    }

    return 0;
}

RHostIp rho_win32_socket_udp_host(RWin32SocketUdp* self)
{
    return rho_wn32_addr_storage_host(&self->storage);
}

#endif
