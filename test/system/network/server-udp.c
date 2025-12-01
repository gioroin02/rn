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

    RnSocketUDP* listener = rnSocketUDPReserve(&arena);

    rnSocketUDPCreate(listener, RnAddressIP_IPv4);

    if (rnSocketUDPBind(listener, rnAddressIPv4Empty(), 50000) == 0)
        return printf("Error during 'bind'\n");

    int len = sizeof(RnSockAddrStorage);
    RnSockAddrStorage local = {0};
    if (getsockname(*((SOCKET*) listener), (RnSockAddr*)&local, &len) == 0) {
        u16 real_port = ntohs(((struct sockaddr_in*)&local)->sin_port);
        printf("Socket realmente boundato sulla porta: %u\n", real_port);
    } else {
        printf("getsockname fallito: %d\n", WSAGetLastError());
    }
    ssize conns = 0;

    while (conns < 2) {
        RnAddressIP address = {0};
        u16         port    = 0;

        u8 msgIn[256] = {0};

        ssize msgInSize = sizeof(msgIn);

        ssize msgInCount = rnSocketUDPReadHost(
            listener, msgIn, msgInSize, &address, &port);

        if (msgInCount > 0) {
            printf("%s\n", msgIn);

            u8 msgOut[] = {"Messaggio da server"};

            ssize msgOutSize  = sizeof(msgOut);
            ssize msgOutCount = sizeof(msgOut);

            rnSocketUDPWriteHost(listener,
                msgOut, msgOutCount, address, port);

            conns += 1;
        }
    }

    rnSocketUDPDestroy(listener);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
