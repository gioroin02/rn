#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    PSocketTcp* listener = pSocketTcpReserve(&arena);

    pSocketTcpCreate(listener, pHostIpMake(pAddressIp4Any(), 50000));
    pSocketTcpBind(listener);
    pSocketTcpListen(listener);

    Int conns = 0;

    for (conns = 0; conns < 2; conns += 1) {
        PSocketTcp* socket = pSocketTcpReserve(&arena);

        pSocketTcpAccept(listener, socket);

        U8 buffer[256];

        pMemorySet(buffer, sizeof buffer, 0x00);

        Int size = pSocketTcpRead(socket, buffer, 0, sizeof buffer);

        printf("%.*s\n", ((int) size), buffer);

        pSocketTcpWrite(socket, buffer, 0, size);
        pSocketTcpDestroy(socket);
    }

    pSocketTcpDestroy(listener);
}
