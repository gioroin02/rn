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
    rnSocketTCPBind(listener, rnAddressIPv4Empty(), 50000);
    rnSocketTCPListen(listener);

    for (ssize i = 0; i < 2; i += 1) {
        RnSocketTCP* client = rnSocketTCPReserve(&arena);

        rnSocketTCPAccept(listener, client);

        u8 msgIn[256] = {0};

        ssize msgInSize  = sizeof(msgIn);
        ssize msgInCount = rnSocketTCPRead(client, msgIn, msgInSize);

        printf("%s\n", msgIn);

        u8 msgOut[] = {"Messaggio da server"};

        ssize msgOutSize  = sizeof(msgOut);
        ssize msgOutCount = sizeof(msgOut);

        rnSocketTCPWrite(client, msgOut, msgOutCount);

        rnSocketTCPDestroy(client);

        rnMemoryArenaRelease(&arena, client);
    }

    rnSocketTCPDestroy(listener);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
