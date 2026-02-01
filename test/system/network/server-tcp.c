#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(rho_memory_mib(2));

    RSocketTcp* listener = rho_socket_tcp_reserve(&arena);

    rho_socket_tcp_create(listener, rho_host_ip_make(rho_address_ip4_any(), 50000));

    rho_socket_tcp_bind(listener);
    rho_socket_tcp_listen(listener);

    for (RInt conns = 0; conns < 2; conns += 1) {
        RSocketTcp* socket = rho_socket_tcp_reserve(&arena);

        rho_socket_tcp_accept(listener, socket);

        RUint8 buffer[256] = {0};

        RInt size = rho_socket_tcp_read(socket, buffer, 0, sizeof buffer);

        printf("%.*s\n", ((int) size), buffer);

        rho_socket_tcp_write(socket, buffer, 0, size);
        rho_socket_tcp_destroy(socket);
    }

    rho_socket_tcp_destroy(listener);
}
