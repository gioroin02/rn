#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxSocketTcp* listener = pxSocketTcpReserve(&arena);

    pxSocketTcpCreate(listener, pxAddressIp4Empty(), 50000);
    pxSocketTcpBind(listener);
    pxSocketTcpListen(listener);

    ssize conns = 0;

    for (conns = 0; conns < 2; conns += 1) {
        PxSocketTcp* socket = pxSocketTcpReserve(&arena);

        pxSocketTcpAccept(listener, socket);

        u8 buffer[256] = {0};

        ssize size = pxSocketTcpRead(socket, buffer, 256);

        printf("%.*s\n", ((int) size), buffer);

        pxSocketTcpWrite(socket, buffer, size);
        pxSocketTcpDestroy(socket);
    }

    pxSocketTcpDestroy(listener);
}
