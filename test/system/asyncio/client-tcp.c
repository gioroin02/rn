#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"
#include "../../../src/system/asyncio/export.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnAsyncIOQueue* queue = rnAsyncIOQueueReserve(&arena);

    rnAsyncIOQueueCreate(queue);

    RnSocketTCP* socket = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(socket, rnAddressIPv4Empty(), 0);

    rnAsyncIOQueueSubmit(queue,
        rnAsyncIOTaskConnect(&arena, 0, socket, rnAddressIPv4Local(), 50000));

    b32 active = 1;

    for (ssize i = 0; i < 1000 && active != 0; i += 1) {
        RnAsyncIOEvent event = {0};

        while (rnAsyncIOQueuePoll(queue, &event, 10) != 0) {
            if (event.kind == RnAsyncIOEvent_Error) active = 0;

            if (event.kind == RnAsyncIOEvent_Connect) {
                if (event.connect.status != 0) {
                    u8*   buffer = rnMemoryArenaReserveManyOf(&arena, u8, 256);
                    ssize stop   = snprintf(((char*) buffer), 256, "Ciao!");

                    rnAsyncIOQueueSubmit(queue,
                        rnAsyncIOTaskWrite(&arena, 0, socket, buffer, 0, stop));
                }
                else active = 0;
            }

            if (event.kind == RnAsyncIOEvent_Write) {
                u8* buffer = rnMemoryArenaReserveManyOf(&arena, u8, 256);

                rnAsyncIOQueueSubmit(queue,
                    rnAsyncIOTaskRead(&arena, 0, socket, buffer, 0, 256));
            }

            if (event.kind == RnAsyncIOEvent_Read) {
                u8*   values = event.read.values;
                ssize stop   = event.read.stop;

                printf("%.*s\n", ((int) stop), values);

                rnSocketTCPDestroy(socket);

                active = 0;
            }
        }
    }

    rnSocketTCPDestroy(socket);
}
