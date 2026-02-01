#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(rho_memory_mib(2));

    RSocketUdp* socket = rho_socket_udp_reserve(&arena);

    rho_socket_udp_create(socket, rho_host_ip_make(rho_address_ip4_any(), 0));

    RUint8 buffer_write[256] = {0};
    RUint8 buffer_read[256]  = {0};

    RInt size = snprintf((char*) buffer_write, sizeof buffer_write, "%s", "Ciao!");

    RHostIp host = rho_host_ip_make(rho_address_ip4_self(), 50000);

    rho_socket_udp_write(socket, buffer_write, 0, size, host);

    size = rho_socket_udp_read(socket, buffer_read, 0, sizeof buffer_read, &host);

    printf("%.*s\n", ((int) size), buffer_read);

    rho_socket_udp_destroy(socket);
}
