#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"
#include "../../../src/system/asyncio/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    rnSystemMemoryStart();
    rnSystemNetworkStart();

    RnMemoryArena arena= rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketTCP* listener = rnSocketTCPReserve(&arena);

    if (rnSocketTCPCreate(listener, RnAddressIP_IPv4) == 0)
        return printf("Error during listener creation: %lu\n", GetLastError());

    if (rnSocketTCPListen(listener, 50000) == 0)
        return printf("Error during listen: %lu\n", GetLastError());

    ssize conns = 0;

    RnWin32AsyncIOQueue* queue = rnWin32AsyncIOQueueReserve(&arena);

    if (rnWin32AsyncIOQueueCreate(queue) == 0)
        return printf("Error during event queue creation: %lu\n", GetLastError());

    if (rnWin32AsyncIOQueueBindSocketTCP(queue, listener) == 0)
        return printf("Error during iocp port creation %lu\n", GetLastError());

    RnSocketTCP* socket = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(socket, RnAddressIP_IPv4);

    rnWin32SocketTCPAcceptAsync(listener, socket, &arena, queue);

    b32 active = 1;

    for (ssize i = 0; active != 0; i += 1) {
        RnAsyncIOEvent event = {0};

        while (rnWin32AsyncIOQueuePoll(queue, &event, 10) != 0) {
            if (event.kind == RnAsyncIOEvent_Accept) {
                RnSocketTCP* socket = event.socket;

                printf("client connected!\n");

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
