#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    PSocketTcp* socket = pSocketTcpReserve(&arena);

    pSocketTcpCreate(socket, pHostIpMake(pAddressIp4Any(), 0));
    pSocketTcpConnect(socket, pHostIpMake(pAddressIp4Self(), 50000));

    U8 buffer_write[256] = {0};
    U8 buffer_read[256]  = {0};

    Int size = snprintf((char*) buffer_write, sizeof buffer_write, "%s", "Ciao!");

    pSocketTcpWrite(socket, buffer_write, 0, size);

    size = pSocketTcpRead(socket, buffer_read, 0, sizeof buffer_read);

    printf("%.*s\n", ((int) size), buffer_read);

    pSocketTcpDestroy(socket);
}
