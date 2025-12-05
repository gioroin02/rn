#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
    rnSystemMemoryStart();
    rnSystemNetworkStart();

    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketUDP* socket = rnSocketUDPReserve(&arena);

    rnSocketUDPCreate(socket, RnAddressIP_IPv4);

    u8 buffer[256] = {"Ciao!"};

    ssize size = strlen(((char*) buffer));

    rnSocketUDPWrite(socket, buffer, size,
        rnAddressIPv4Local(), 50000);

    memset(buffer, 0, 256);

    size = rnSocketUDPRead(socket, buffer, 256, 0, 0);

    printf("%.*s\n", ((int) size), buffer);

    rnSocketUDPDestroy(socket);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
