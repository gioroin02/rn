#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/network/export.h"
#include "../../../src/system/asyncio/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
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

    for (ssize i = 0; i < 1000 && active != 0; i += 1) {
        RnAsyncIOEvent event = {0};

        while (rnAsyncIOQueuePoll(queue, &event, 10) != 0) {
            if (event.kind == RnAsyncIOEvent_Error) active = 0;

            if (event.kind == RnAsyncIOEvent_Accept) {
                RnSocketTCP* socket = event.accept.value;

                printf("client connected %lli!\n", i);

                u8* buffer = rnMemoryArenaReserveManyOf(&arena, u8, 256);

                rnAsyncIOQueueSubmit(queue,
                    rnAsyncIOTaskRead(&arena, socket, buffer, 256));

                RnSocketTCP* other = rnSocketTCPReserve(&arena);

                rnAsyncIOQueueSubmit(queue,
                    rnAsyncIOTaskAccept(&arena, listener, other));
            }

            if (event.kind == RnAsyncIOEvent_Read) {
                RnSocketTCP* socket = event.read.socket;
                u8*          buffer = event.read.buffer;
                ssize        count  = event.read.count;

                printf("%.*s\n", ((int) count), buffer);

                rnAsyncIOQueueSubmit(queue,
                    rnAsyncIOTaskWrite(&arena, socket, buffer, count));
            }

            if (event.kind == RnAsyncIOEvent_Write)
                rnSocketTCPDestroy(event.write.socket);
        }
    }

    rnSocketTCPDestroy(listener);
}
