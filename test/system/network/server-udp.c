#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMebi(2));

    PxSocketUdp* socket = pxSocketUdpReserve(&arena);

    pxSocketUdpCreate(socket, pxAddressIp4Empty(), 50000);
    pxSocketUdpBind(socket);

    ssize conns = 0;

    for (conns = 0; conns < 2; conns += 1) {
        PxAddressIp address;
        u16         port;

        u8 buffer[256];

        pxMemorySet(buffer, sizeof buffer, 0x00);

        ssize size = pxSocketUdpRead(socket, buffer,
            0, sizeof buffer, &address, &port);

        printf("%.*s\n", ((int) size), buffer);

        pxSocketUdpWrite(socket, buffer, 0, size, address, port);
    }

    pxSocketUdpDestroy(socket);
}
