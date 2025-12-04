#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"
#include "../../../src/system/asyncio/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    rnSystemMemoryStart();

    if (rnSystemNetworkStart() == 0)
        return printf("Error during network startup\n");

    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketTCP* listener = rnSocketTCPReserve(&arena);

    if (rnSocketTCPCreate(listener, RnAddressIP_IPv4) == 0)
        return printf("Error during listener creation: %i\n", WSAGetLastError());

    if (rnSocketTCPBind(listener, 50000) == 0)
        return printf("Error during bind: %i\n", WSAGetLastError());

    if (rnSocketTCPListen(listener) == 0)
        return printf("Error during listen: %i\n", WSAGetLastError());

    RnWin32AsyncIOQueue* queue = rnWin32AsyncIOQueueReserve(&arena);

    if (rnWin32AsyncIOQueueCreate(queue) == 0)
        return printf("Error during event queue creation: %i\n", WSAGetLastError());

    rnWin32AsyncIOQueueBindSocketTCP(queue, listener);

    ssize conns = 0;

    RnSocketTCP* socket = rnSocketTCPReserve(&arena);

    if (rnSocketTCPCreate(socket, RnAddressIP_IPv4) == 0)
        return printf("Error creating socket\n");

    rnWin32SocketTCPAcceptAsync(
        listener, socket, &arena, queue);

    b32 active = 1;

    for (ssize i = 0; active != 0 && i < 1000000; i += 1) {
        RnAsyncIOEvent event = {0};

        while (rnWin32AsyncIOQueuePoll(queue, &event, 10) != 0) {
            if (event.kind == RnAsyncIOEvent_Accept) {
                RnSocketTCP* socket = event.socket;

                printf("client connected! %lli\n", i);

                rnSocketTCPDestroy(socket);

                socket = rnSocketTCPReserve(&arena);

                rnSocketTCPCreate(socket, RnAddressIP_IPv4);

                rnWin32SocketTCPAcceptAsync(
                    listener, socket, &arena, queue);
            }

            if (event.kind == RnAsyncIOEvent_Error)
                active = 0;
        }

        // printf("%lli\n", i);
    }
}
