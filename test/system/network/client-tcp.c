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

    RnSocketTCP* socket = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(socket, RnAddressIP_IPv4);
    rnSocketTCPConnect(socket, rnAddressIPv4Local(), 50000);

    u8 msgOut[] = {"Messaggio da client"};

    ssize msgOutSize  = sizeof(msgOut);
    ssize msgOutCount = sizeof(msgOut);

    rnSocketTCPWrite(socket, msgOut, msgOutCount);

    u8 msgIn[256] = {0};

    ssize msgInSize  = sizeof(msgIn);
    ssize msgInCount = rnSocketTCPRead(socket, msgIn, msgInSize);

    printf("%s\n", msgIn);

    rnSocketTCPDestroy(socket);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
