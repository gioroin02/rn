#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxAddressIP client = pxAddressIPv6Local();
    PxAddressIP server = pxAddressIPv6Make(192, 168, 0, 0, 0, 0, 1, 2);

    printf("client = (PxAddressIP) {");
    for (ssize i = 0; i < PX_ADDRESS_IPV6_SIZE; i += 1)
        printf("%3u%s", client.ipv6.values[i], i + 1 < PX_ADDRESS_IPV6_SIZE ? ", " : "");
    printf("}\n");

    printf("server = (PxAddressIP) {");
    for (ssize i = 0; i < PX_ADDRESS_IPV6_SIZE; i += 1)
        printf("%3u%s", server.ipv6.values[i], i + 1 < PX_ADDRESS_IPV6_SIZE ? ", " : "");
    printf("}\n");
}
