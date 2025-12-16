#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxSocketTCP* listener = pxSocketTCPReserve(&arena);

    pxSocketTCPCreate(listener, pxAddressIPv4Empty(), 50000);
    pxSocketTCPBind(listener);
    pxSocketTCPListen(listener);

    for (ssize conns = 0; conns < 2; conns += 1) {
        PxSocketTCP* socket = pxSocketTCPReserve(&arena);

        pxSocketTCPAccept(listener, socket);

        u8 buffer[256] = {0};

        ssize size = pxSocketTCPRead(socket, buffer, 256);

        printf("%.*s\n", ((int) size), buffer);

        pxSocketTCPWrite(socket, buffer, size);
        pxSocketTCPDestroy(socket);
    }

    pxSocketTCPDestroy(listener);
}
