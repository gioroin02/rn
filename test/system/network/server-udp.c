#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(rho_memory_mib(2));

    RSocketUdp* socket = rho_socket_udp_reserve(&arena);

    rho_socket_udp_create(socket, rho_host_ip_make(rho_address_ip4_any(), 50000));

    rho_socket_udp_bind(socket);

    for (RInt conns = 0; conns < 2; conns += 1) {
        RHostIp host = rho_host_ip_make(rho_address_ip4_any(), 0);

        RUint8 buffer[256] = {0};

        RInt size = rho_socket_udp_read(socket, buffer, 0, sizeof buffer, &host);

        printf("%.*s\n", ((int) size), buffer);

        rho_socket_udp_write(socket, buffer, 0, size, host);
    }

    rho_socket_udp_destroy(socket);
}
