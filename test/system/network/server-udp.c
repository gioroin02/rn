#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

#include <winsock2.h>
#include <ws2tcpip.h>

typedef struct sockaddr_storage RnSockAddrStorage;

typedef struct sockaddr     RnSockAddr;
typedef struct sockaddr_in  RnSockAddrIn4;
typedef struct sockaddr_in6 RnSockAddrIn6;

int
main(int argc, char** argv)
{
    rnSystemMemoryStart();
    rnSystemNetworkStart();

    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketUDP* socket = rnSocketUDPReserve(&arena);

    rnSocketUDPCreate(socket, RnAddressIP_IPv4);
    rnSocketUDPBind(socket, 50000);

    for (ssize conns = 0; conns < 2; conns += 1) {
        RnAddressIP address = {0};
        u16         port    = 0;

        u8 buffer[256] = {0};

        ssize size = rnSocketUDPRead(socket, buffer, 256, &address, &port);

        printf("%.*s\n", ((int) size), buffer);

        rnSocketUDPWrite(socket, buffer, size, address, port);
    }

    rnSocketUDPDestroy(socket);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
