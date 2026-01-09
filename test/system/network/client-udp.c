#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(2));

    PxSocketUdp* socket = pxSocketUdpReserve(&arena);

    pxSocketUdpCreate(socket, pxAddressIp4Empty(), 0);

    u8 buffer[256];

    pxMemorySet(buffer, sizeof buffer, 0x00);

    ssize size = snprintf((char*) buffer, sizeof buffer, "%s", "Ciao!");

    pxSocketUdpWrite(socket, buffer,
        0, size, pxAddressIp4Local(), 50000);

    pxMemorySet(buffer, sizeof buffer, 0x00);

    size = pxSocketUdpRead(socket, buffer, 0, sizeof buffer, 0, 0);

    printf("%.*s\n", ((int) size), buffer);

    pxSocketUdpDestroy(socket);
}
