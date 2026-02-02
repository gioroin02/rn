#include "../../../src/rho-system/memory/export.h"
#include "../../../src/rho-system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(rho_memory_mib(2));

    RSocketTcp* socket = rho_socket_tcp_reserve(&arena);

    rho_socket_tcp_create(socket,  rho_host_ip_make(rho_address_ip4_any(), 0));
    rho_socket_tcp_connect(socket, rho_host_ip_make(rho_address_ip4_self(), 50000));

    RUint8 buffer_write[256] = {0};
    RUint8 buffer_read[256]  = {0};

    RInt size = snprintf((RChar8*) buffer_write, sizeof buffer_write, "%s", "Ciao!");

    rho_socket_tcp_write(socket, buffer_write, 0, size);

    size = rho_socket_tcp_read(socket, buffer_read, 0, sizeof buffer_read);

    printf("%.*s\n", ((int) size), buffer_read);

    rho_socket_tcp_destroy(socket);
}
