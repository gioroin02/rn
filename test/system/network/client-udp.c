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

    RnSocketUDP* server = rnSocketUDPReserve(&arena);

    rnSocketUDPCreate(server, RnAddressIP_IPv4);

    u8 msgOut[] = {"Messaggio da client"};

    ssize msgOutSize  = sizeof(msgOut);
    ssize msgOutCount = sizeof(msgOut);

    rnSocketUDPWriteHost(server, msgOut, msgOutCount,
        rnAddressIPv4Local(), 50000);

    RnAddressIP address = {0};
    u16         port    = 0;

    u8 msgIn[256] = {0};

    ssize msgInSize = sizeof(msgIn);

    ssize msgInCount = rnSocketUDPReadHost(
        server, msgIn, msgInSize, &address, &port);

    if (msgInCount > 0) printf("%s\n", msgIn);

    rnSocketUDPDestroy(server);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
