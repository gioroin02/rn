#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    PSocketTcp* socket = pSocketTcpReserve(&arena);

    pSocketTcpCreate(socket, pHostIpMake(pAddressIp4Any(), 0));
    pSocketTcpConnect(socket, pHostIpMake(pAddressIp4Self(), 50000));

    U8 buffer[256];

    pMemorySet(buffer, sizeof buffer, 0x00);

    Int size = snprintf((char*) buffer, sizeof buffer, "%s", "Ciao!");

    pSocketTcpWrite(socket, buffer, 0, size);

    pMemorySet(buffer, sizeof buffer, 0x00);

    size = pSocketTcpRead(socket, buffer, 0, sizeof buffer);

    printf("%.*s\n", ((int) size), buffer);

    pSocketTcpDestroy(socket);
}
