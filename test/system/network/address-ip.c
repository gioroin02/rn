#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxAddressIp client = pxAddressIp6Local();
    PxAddressIp server = pxAddressIp6Make(192, 168, 0, 0, 0, 0, 1, 2);

    ssize index = 0;

    printf("client = (PxAddressIp) {");
    for (index = 0; index < PX_ADDRESS_IP6_SIZE; index += 1)
        printf("%3u%s", client.ip6.values[index], index + 1 < PX_ADDRESS_IP6_SIZE ? ", " : "");
    printf("}\n");

    printf("server = (PxAddressIp) {");
    for (index = 0; index < PX_ADDRESS_IP6_SIZE; index += 1)
        printf("%3u%s", server.ip6.values[index], index + 1 < PX_ADDRESS_IP6_SIZE ? ", " : "");
    printf("}\n");
}
