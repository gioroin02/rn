#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketTCP* listener = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(listener, rnAddressIPv4Empty(), 50000);
    rnSocketTCPBind(listener);
    rnSocketTCPListen(listener);

    for (ssize conns = 0; conns < 2; conns += 1) {
        RnSocketTCP* socket = rnSocketTCPReserve(&arena);

        rnSocketTCPAccept(listener, socket);

        u8 buffer[256] = {0};

        ssize size = rnSocketTCPRead(socket, buffer, 256);

        printf("%.*s\n", ((int) size), buffer);

        rnSocketTCPWrite(socket, buffer, size);
        rnSocketTCPDestroy(socket);
    }

    rnSocketTCPDestroy(listener);
}
