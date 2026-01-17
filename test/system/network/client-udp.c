#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    PSocketUdp* socket = pSocketUdpReserve(&arena);

    pSocketUdpCreate(socket, pHostIpMake(pAddressIp4Any(), 0));

    U8 buffer[256];

    pMemorySet(buffer, sizeof buffer, 0x00);

    Int size = snprintf((char*) buffer, sizeof buffer, "%s", "Ciao!");

    PHostIp host = pHostIpMake(pAddressIp4Self(), 50000);

    pSocketUdpWrite(socket, buffer, 0, size, host);

    pMemorySet(buffer, sizeof buffer, 0x00);

    size = pSocketUdpRead(socket, buffer, 0, sizeof buffer, &host);

    printf("%.*s\n", ((int) size), buffer);

    pSocketUdpDestroy(socket);
}
