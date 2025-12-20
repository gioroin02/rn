#include "../../../src/base/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxSocketTcp* socket = pxSocketTcpReserve(&arena);

    pxSocketTcpCreate(socket, pxAddressIp4Empty(), 0);
    pxSocketTcpConnect(socket, pxAddressIp4Local(), 50000);

    u8 buffer[256] = {"Ciao!"};

    ssize size = strlen(((char*) buffer));

    pxSocketTcpWrite(socket, buffer, size);

    memset(buffer, 0, 256);

    size = pxSocketTcpRead(socket, buffer, 256);

    printf("%.*s\n", ((int) size), buffer);

    pxSocketTcpDestroy(socket);
}
