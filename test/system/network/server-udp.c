#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxSocketUdp* socket = pxSocketUdpReserve(&arena);

    pxSocketUdpCreate(socket, pxAddressIp4Empty(), 50000);
    pxSocketUdpBind(socket);

    ssize conns = 0;

    for (conns = 0; conns < 2; conns += 1) {
        PxAddressIp address = {0};
        u16         port    = 0;

        u8 buffer[256] = {0};

        ssize size = pxSocketUdpRead(socket, buffer, 256, &address, &port);

        printf("%.*s\n", ((int) size), buffer);

        pxSocketUdpWrite(socket, buffer, size, address, port);
    }

    pxSocketUdpDestroy(socket);
}
