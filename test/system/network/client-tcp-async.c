#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/asyncio/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>
#include <string.h>

typedef struct ClientState
{
    RnMemoryArena*  arena;
    RnAsyncIOQueue* queue;
    RnSocketTCP*    socket;

    b32 active;
}
ClientState;

void
clientOnSocketTCPEvent(ClientState* self, RnSocketTCPEvent* event)
{
    switch (event->kind) {
        case RnSocketTCPAsync_Error: self->active = 0; break;

        case RnSocketTCPAsync_Connect: {
            if (event->connect.status != 0) {
                printf("[DEBUG] Connected!\n");

                u8*   buffer = rnMemoryArenaReserveManyOf(self->arena, u8, 256);
                ssize stop   = snprintf(((char*) buffer), 256, "Ciao!");

                rnAsyncIOQueueSubmit(self->queue, rnSocketTCPAsyncWrite(
                    self->arena, self, &clientOnSocketTCPEvent, self->socket, buffer, 0, stop));
            }
            else self->active = 0;
        } break;

        case RnSocketTCPAsync_Write: {
            printf("[DEBUG] Wrote message!\n");

            u8* buffer = rnMemoryArenaReserveManyOf(self->arena, u8, 256);

            rnAsyncIOQueueSubmit(self->queue, rnSocketTCPAsyncRead(
                self->arena, self, &clientOnSocketTCPEvent, self->socket, buffer, 0, 256));
        } break;

        case RnSocketTCPAsync_Read: {
            printf("[DEBUG] Read message!\n");

            u8*   values = event->read.values;
            ssize stop   = event->read.stop;

            printf("%.*s\n", ((int) stop), values);

            rnSocketTCPDestroy(self->socket);

            self->active = 0;
        } break;

        default: break;
    }
}

int
main(int argc, char** argv)
{
    RnMemoryArena arena = rnSystemMemoryReserve(rnMemoryMiB(2));

    RnAddressIP address = rnAddressIPv4Local();
    u16         port    = 50000;

    ClientState client = {0};

    client.arena  = &arena;
    client.queue  = rnAsyncIOQueueReserve(&arena);
    client.socket = rnSocketTCPReserve(&arena);

    rnAsyncIOQueueCreate(client.queue);
    rnSocketTCPCreate(client.socket, rnAddressIPv4Empty(), 0);

    client.active = 1;

    rnAsyncIOQueueSubmit(client.queue, rnSocketTCPAsyncConnect(
        &arena, &client, &clientOnSocketTCPEvent, client.socket, address, port));

    for (ssize i = 0; i < 1000 && client.active != 0; i += 1)
        rnAsyncIOQueuePoll(client.queue, 10);

    rnSocketTCPDestroy(client.socket);
}
