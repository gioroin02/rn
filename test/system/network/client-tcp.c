#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketTCP* socket = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(socket, RnAddressIP_IPv4);
    rnSocketTCPConnect(socket, rnAddressIPv4Local(), 50000);

    u8 buffer[256] = {"Ciao!"};

    ssize size = strlen(((char*) buffer));

    rnSocketTCPWrite(socket, buffer, size);

    memset(buffer, 0, 256);

    size = rnSocketTCPRead(socket, buffer, 256);

    printf("%.*s\n", ((int) size), buffer);

    rnSocketTCPDestroy(socket);
}
