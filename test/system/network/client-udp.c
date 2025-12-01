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

    RnSocketUDP* socket = rnSocketUDPReserve(&arena);

    rnSocketUDPCreate(socket, RnAddressIP_IPv4);

    u8 msgOut[] = {"Messaggio da client"};

    ssize msgOutSize  = sizeof(msgOut);
    ssize msgOutCount = sizeof(msgOut);

    rnSocketUDPWriteHost(socket, msgOut, msgOutCount, rnAddressIPv4Local(), 50000);

    u8 msgIn[256] = {0};

    ssize msgInSize  = sizeof(msgIn);
    ssize msgInCount = rnSocketUDPReadHost(socket, msgIn, msgInSize, 0, 0);

    printf("%s\n", msgIn);

    rnSocketUDPDestroy(socket);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
