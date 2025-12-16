#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/asyncio/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>

typedef struct ServerState
{
    PxMemoryArena*  arena;
    PxAsyncIOQueue* queue;
    PxSocketTCP*    listener;
    PxSocketTCP*    socket;

    b32 active;
}
ServerState;

void
serverOnSocketTCPEvent(ServerState* self, PxSocketTCPEvent* event)
{
    if (event->kind == PxAsyncIOEvent_Error) active = 0;

    if (event->kind == PxAsyncIOEvent_Accept) {
        PxSocketTCP* socket = event->accept.socket;

        printf("client connected %lli!\n", i);

        u8* buffer = pxMemoryArenaReserveManyOf(&arena, u8, 256);

        pxAsyncIOQueueSubmit(queue,
            pxAsyncIOTaskRead(&arena, 0, socket, buffer, 0, 256));

        PxSocketTCP* other = pxSocketTCPReserve(&arena);

        pxAsyncIOQueueSubmit(queue,
            pxAsyncIOTaskAccept(&arena, 0, listener, other));
    }

    if (event->kind == PxAsyncIOEvent_Read) {
        PxSocketTCP* socket = event->read.socket;
        u8*          values = event->read.values;
        ssize        stop   = event->read.stop;

        printf("%.*s\n", ((int) stop), values);

        pxAsyncIOQueueSubmit(queue,
            pxAsyncIOTaskWrite(&arena, 0, socket, values, 0, stop));
    }

    if (event->kind == PxAsyncIOEvent_Write)
        pxSocketTCPDestroy(event->write.socket);
}

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxAddressIP address = pxAddressIPv4Local();
    u16         port    = 50000;

    ServerState server = {0};

    server.arena    = &arena;
    server.queue    = pxAsyncIOQueueReserve(&arena);
    server.listener = pxSocketTCPReserve(&arena);

    pxAsyncIOQueueCreate(server.queue);
    pxSocketTCPCreate(server.listener, address, port);
    pxSocketTCPBind(server.listener);
    pxSocketTCPListen(server.listener);

    server.active = 1;

    PxSocketTCP* socket = pxSocketTCPReserve(&arena);

    pxAsyncIOQueueSubmit(server.queue, pxSocketTCPAsyncAccept(
        &arena, &server, &serverOnSocketTCPEvent, listener, socket));

    for (ssize i = 0; i < 1000 && server.active != 0; i += 1)
        pxAsyncIOQueuePoll(server.queue, 10);

    pxSocketTCPDestroy(server.listener);
}
