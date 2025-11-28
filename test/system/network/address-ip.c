#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    RnAddressIP client = rnAddressIPv6Local();
    RnAddressIP server = rnAddressIPv6Make(192, 168, 0, 0, 0, 0, 1, 2);

    printf("client = (RnAddressIP) {");
    for (ssize i = 0; i < RN_ADDRESS_IPV6_SIZE; i += 1)
        printf("%3u%s", client.ipv6.values[i], i + 1 < RN_ADDRESS_IPV6_SIZE ? ", " : "");
    printf("}\n");

    printf("server = (RnAddressIP) {");
    for (ssize i = 0; i < RN_ADDRESS_IPV6_SIZE; i += 1)
        printf("%3u%s", server.ipv6.values[i], i + 1 < RN_ADDRESS_IPV6_SIZE ? ", " : "");
    printf("}\n");
}
