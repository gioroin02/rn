#include "../../../src/rho-system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RAddressIp client = rho_address_ip6_self();
    RAddressIp server = rho_address_ip6_make(192, 168, 0, 0, 0, 0, 1, 2);

    printf("client = (RAddressIp) {");
    for (RInt i = 0; i < RHO_ADDRESS_IP6_SIZE; i += 1)
        printf("%3u%s", client.ip6.values[i], i + 1 < RHO_ADDRESS_IP6_SIZE ? ", " : "");
    printf("}\n");

    printf("server = (RAddressIp) {");
    for (RInt i = 0; i < RHO_ADDRESS_IP6_SIZE; i += 1)
        printf("%3u%s", server.ip6.values[i], i + 1 < RHO_ADDRESS_IP6_SIZE ? ", " : "");
    printf("}\n");
}
