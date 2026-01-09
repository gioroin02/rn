#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(2));

    PxSocketTcp* socket = pxSocketTcpReserve(&arena);

    pxSocketTcpCreate(socket, pxAddressIp4Empty(), 0);
    pxSocketTcpConnect(socket, pxAddressIp4Local(), 50000);

    u8 buffer[256];

    pxMemorySet(buffer, sizeof buffer, 0x00);

    ssize size = snprintf((char*) buffer, sizeof buffer, "%s", "Ciao!");

    pxSocketTcpWrite(socket, buffer, 0, size);

    pxMemorySet(buffer, sizeof buffer, 0x00);

    size = pxSocketTcpRead(socket, buffer, 0, sizeof buffer);

    printf("%.*s\n", ((int) size), buffer);

    pxSocketTcpDestroy(socket);
}
