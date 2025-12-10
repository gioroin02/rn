#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketUDP* socket = rnSocketUDPReserve(&arena);

    rnSocketUDPCreate(socket, rnAddressIPv4Empty(), 50000);
    rnSocketUDPBind(socket);

    for (ssize conns = 0; conns < 2; conns += 1) {
        RnAddressIP address = {0};
        u16         port    = 0;

        u8 buffer[256] = {0};

        ssize size = rnSocketUDPRead(socket, buffer, 256, &address, &port);

        printf("%.*s\n", ((int) size), buffer);

        rnSocketUDPWrite(socket, buffer, size, address, port);
    }

    rnSocketUDPDestroy(socket);
}
