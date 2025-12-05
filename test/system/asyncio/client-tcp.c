#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"
#include "../../../src/system/asyncio/export.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
    rnSystemMemoryStart();
    rnSystemNetworkStart();

    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnSocketTCP* socket = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(socket, RnAddressIP_IPv4);

    RnAsyncIOQueue* queue = rnAsyncIOQueueReserve(&arena);

    rnAsyncIOQueueCreate(queue);

    rnAsyncIOQueueSubmit(queue,
        rnAsyncIOTaskConnect(&arena, socket, rnAddressIPv4Local(), 50000));

    b32 active = 1;

    while (active != 0) {
        RnAsyncIOEvent event = {0};

        while (rnAsyncIOQueuePoll(queue, &event, 10) != 0) {
            if (event.kind == RnAsyncIOEvent_Error)
                active = 0;

            if (event.kind == RnAsyncIOEvent_Connect) {
                if (event.connect.status != 0) {
                    u8 buffer[256] = {"Ciao!"};

                    ssize size = strlen(((char*) buffer));

                    rnSocketTCPWrite(socket, buffer, size);

                    memset(buffer, 0, 256);

                    size = rnSocketTCPRead(socket, buffer, 256);

                    printf("%.*s\n", ((int) size), buffer);
                }

                active = 0;
            }
        }
    }

    rnSocketTCPDestroy(socket);

    rnSystemNetworkStop();
    rnSystemMemoryStop();
}
