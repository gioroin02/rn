#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/asyncio/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnAsyncIOQueue* queue = rnAsyncIOQueueReserve(&arena);

    rnAsyncIOQueueCreate(queue);

    RnSocketTCP* listener = rnSocketTCPReserve(&arena);

    rnSocketTCPCreate(listener, rnAddressIPv4Empty(), 50000);
    rnSocketTCPBind(listener);
    rnSocketTCPListen(listener);

    RnSocketTCP* socket = rnSocketTCPReserve(&arena);

    rnAsyncIOQueueSubmit(queue,
        rnAsyncIOTaskAccept(&arena, 0, listener, socket));

    b32   active = 1;
    ssize conns  = 0;

    for (ssize i = 0; i < 1000 && active != 0; i += 1) {
        RnAsyncIOEvent event = {0};

        while (rnAsyncIOQueuePoll(queue, &event, 10) != 0) {
            if (event.kind == RnAsyncIOEvent_Error) active = 0;

            if (event.kind == RnAsyncIOEvent_Accept) {
                RnSocketTCP* socket = event.accept.socket;

                printf("client connected %lli!\n", i);

                u8* buffer = rnMemoryArenaReserveManyOf(&arena, u8, 256);

                rnAsyncIOQueueSubmit(queue,
                    rnAsyncIOTaskRead(&arena, 0, socket, buffer, 0, 256));

                RnSocketTCP* other = rnSocketTCPReserve(&arena);

                rnAsyncIOQueueSubmit(queue,
                    rnAsyncIOTaskAccept(&arena, 0, listener, other));
            }

            if (event.kind == RnAsyncIOEvent_Read) {
                RnSocketTCP* socket = event.read.socket;
                u8*          values = event.read.values;
                ssize        stop   = event.read.stop;

                printf("%.*s\n", ((int) stop), values);

                rnAsyncIOQueueSubmit(queue,
                    rnAsyncIOTaskWrite(&arena, 0, socket, values, 0, stop));
            }

            if (event.kind == RnAsyncIOEvent_Write)
                rnSocketTCPDestroy(event.write.socket);
        }
    }

    rnSocketTCPDestroy(listener);
}
