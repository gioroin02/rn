#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    rnSystemMemoryStart();
    rnSystemNetworkStart();

    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketTCP* listener = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(listener, RnAddressIP_IPv4);

    if (rnSocketTCPListen(listener, 50000) == 0)
        return printf("Error during listen\n");

    for (ssize conns = 0; conns < 2; conns += 1) {
        RnSocketTCP* socket = rnSocketTCPReserve(&arena);

        rnSocketTCPAccept(listener, socket);

        u8 msgIn[256] = {0};

        ssize msgInSize  = sizeof(msgIn);
        ssize msgInCount = rnSocketTCPRead(socket, msgIn, msgInSize);

        printf("%s\n", msgIn);

        u8 msgOut[] = {"Messaggio da server"};

        ssize msgOutSize  = sizeof(msgOut);
        ssize msgOutCount = sizeof(msgOut);

        rnSocketTCPWrite(socket, msgOut, msgOutCount);

        rnSocketTCPDestroy(socket);

        rnMemoryArenaRelease(&arena, socket);
    }

    rnSocketTCPDestroy(listener);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
