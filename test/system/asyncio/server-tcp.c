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

    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketTCP* listener = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(listener, RnAddressIP_IPv4);

    rnSocketTCPBind(listener, 50000);
    rnSocketTCPListen(listener);

    RnAsyncIOQueue* queue = rnAsyncIOQueueReserve(&arena);

    rnAsyncIOQueueCreate(queue);

    RnSocketTCP* socket = rnSocketTCPReserve(&arena);

    rnAsyncIOQueueSubmit(queue,
        rnAsyncIOTaskAccept(&arena, listener, socket));

    b32   active = 1;
    ssize conns  = 0;

    for (ssize i = 0; active != 0 && i < 1000; i += 1) {
        RnAsyncIOEvent event = {0};

        while (rnAsyncIOQueuePoll(queue, &event, 10) != 0) {
            if (event.kind == RnAsyncIOEvent_Error)
                active = 0;

            if (event.kind == RnAsyncIOEvent_Accept) {
                RnSocketTCP* socket = event.accept.socket;

                printf("client connected %lli!\n", i);

                u8 buffer[256] = {0};

                ssize size = rnSocketTCPRead(socket, buffer, 256);

                printf("%.*s\n", ((int) size), buffer);

                rnSocketTCPWrite(socket, buffer, size);
                rnSocketTCPDestroy(socket);

                rnAsyncIOQueueSubmit(queue,
                    rnAsyncIOTaskAccept(&arena, listener, socket));
            }
        }
    }

    rnSocketTCPDestroy(listener);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
