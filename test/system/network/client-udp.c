#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    PSocketUdp* socket = pSocketUdpReserve(&arena);

    pSocketUdpCreate(socket, pHostIpMake(pAddressIp4Any(), 0));

    U8 buffer_write[256] = {0};
    U8 buffer_read[256]  = {0};

    Int size = snprintf((char*) buffer_write, sizeof buffer_write, "%s", "Ciao!");

    PHostIp host = pHostIpMake(pAddressIp4Self(), 50000);

    pSocketUdpWrite(socket, buffer_write, 0, size, host);

    size = pSocketUdpRead(socket, buffer_read, 0, sizeof buffer_read, &host);

    printf("%.*s\n", ((int) size), buffer_read);

    pSocketUdpDestroy(socket);
}
