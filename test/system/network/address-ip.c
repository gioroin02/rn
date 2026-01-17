#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PAddressIp client = pAddressIp6Self();
    PAddressIp server = pAddressIp6Make(192, 168, 0, 0, 0, 0, 1, 2);

    Int index = 0;

    printf("client = (PAddressIp) {");
    for (index = 0; index < P_ADDRESS_IP6_SIZE; index += 1)
        printf("%3u%s", client.ip6.values[index], index + 1 < P_ADDRESS_IP6_SIZE ? ", " : "");
    printf("}\n");

    printf("server = (PAddressIp) {");
    for (index = 0; index < P_ADDRESS_IP6_SIZE; index += 1)
        printf("%3u%s", server.ip6.values[index], index + 1 < P_ADDRESS_IP6_SIZE ? ", " : "");
    printf("}\n");
}
