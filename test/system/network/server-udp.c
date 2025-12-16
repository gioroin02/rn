#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxSocketUDP* socket = pxSocketUDPReserve(&arena);

    pxSocketUDPCreate(socket, pxAddressIPv4Empty(), 50000);
    pxSocketUDPBind(socket);

    for (ssize conns = 0; conns < 2; conns += 1) {
        PxAddressIP address = {0};
        u16         port    = 0;

        u8 buffer[256] = {0};

        ssize size = pxSocketUDPRead(socket, buffer, 256, &address, &port);

        printf("%.*s\n", ((int) size), buffer);

        pxSocketUDPWrite(socket, buffer, size, address, port);
    }

    pxSocketUDPDestroy(socket);
}
