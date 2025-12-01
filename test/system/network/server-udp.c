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

    rnSocketUDPCreate(socket, RnAddressIP_IPv6);

    if (rnSocketUDPListen(socket, 50000) == 0)
        return printf("Error during 'bind'\n");

    int len = sizeof(RnSockAddrStorage);
    RnSockAddrStorage local = {0};
    if (getsockname(*((SOCKET*) socket), (RnSockAddr*)&local, &len) == 0) {
        u16 real_port = ntohs(((struct sockaddr_in*)&local)->sin_port);
        printf("Porta del socket: %u\n", real_port);
    } else {
        printf("getsockname fallito: %d\n", WSAGetLastError());
    }

    for (ssize conns = 0; conns < 2;) {
        RnAddressIP address = {0};
        u16         port    = 0;

        u8 msgIn[256] = {0};

        ssize msgInSize  = sizeof(msgIn);
        ssize msgInCount = rnSocketUDPReadHost(socket, msgIn, msgInSize, &address, &port);

        if (msgInCount > 0) {
            printf("%s\n", msgIn);

            u8 msgOut[] = {"Messaggio da server"};

            ssize msgOutSize  = sizeof(msgOut);
            ssize msgOutCount = sizeof(msgOut);

            rnSocketUDPWriteHost(socket, msgOut, msgOutCount, address, port);

            conns += 1;
        }
    }

    rnSocketUDPDestroy(socket);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
