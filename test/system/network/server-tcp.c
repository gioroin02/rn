#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMebi(2));

    PxSocketTcp* listener = pxSocketTcpReserve(&arena);

    pxSocketTcpCreate(listener, pxAddressIp4Empty(), 50000);
    pxSocketTcpBind(listener);
    pxSocketTcpListen(listener);

    ssize conns = 0;

    for (conns = 0; conns < 2; conns += 1) {
        PxSocketTcp* socket = pxSocketTcpReserve(&arena);

        pxSocketTcpAccept(listener, socket);

        u8 buffer[256];

        pxMemorySet(buffer, sizeof buffer, 0x00);

        ssize size = pxSocketTcpRead(socket, buffer, 0, sizeof buffer);

        printf("%.*s\n", ((int) size), buffer);

        pxSocketTcpWrite(socket, buffer, 0, size);
        pxSocketTcpDestroy(socket);
    }

    pxSocketTcpDestroy(listener);
}
