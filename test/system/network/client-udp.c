#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxSocketUDP* socket = pxSocketUDPReserve(&arena);

    pxSocketUDPCreate(socket, pxAddressIPv4Empty(), 0);

    u8 buffer[256] = {"Ciao!"};

    ssize size = strlen(((char*) buffer));

    pxSocketUDPWrite(socket, buffer, size,
        pxAddressIPv4Local(), 50000);

    memset(buffer, 0, 256);

    size = pxSocketUDPRead(socket, buffer, 256, 0, 0);

    printf("%.*s\n", ((int) size), buffer);

    pxSocketUDPDestroy(socket);
}
