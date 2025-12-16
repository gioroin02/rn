#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxSocketTCP* socket = pxSocketTCPReserve(&arena);

    pxSocketTCPCreate(socket, pxAddressIPv4Empty(), 0);
    pxSocketTCPConnect(socket, pxAddressIPv4Local(), 50000);

    u8 buffer[256] = {"Ciao!"};

    ssize size = strlen(((char*) buffer));

    pxSocketTCPWrite(socket, buffer, size);

    memset(buffer, 0, 256);

    size = pxSocketTCPRead(socket, buffer, 256);

    printf("%.*s\n", ((int) size), buffer);

    pxSocketTCPDestroy(socket);
}
