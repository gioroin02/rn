#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxSocketUdp* socket = pxSocketUdpReserve(&arena);

    pxSocketUdpCreate(socket, pxAddressIp4Empty(), 0);

    u8 buffer[256] = {"Ciao!"};

    ssize size = strlen(((char*) buffer));

    pxSocketUdpWrite(socket, buffer, size,
        pxAddressIp4Local(), 50000);

    memset(buffer, 0, 256);

    size = pxSocketUdpRead(socket, buffer, 256, 0, 0);

    printf("%.*s\n", ((int) size), buffer);

    pxSocketUdpDestroy(socket);
}
