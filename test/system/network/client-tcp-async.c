#include "../../../src/base/memory/export.h"

#include "../../../src/system/memory/export.h"
#include "../../../src/system/asyncio/export.h"
#include "../../../src/system/network/export.h"

#include <stdio.h>
#include <string.h>

typedef struct ClientState
{
    PxMemoryArena*  arena;
    PxAsyncIOQueue* queue;
    PxSocketTCP*    socket;

    b32 active;
}
ClientState;

void
clientOnSocketTCPEvent(ClientState* self, PxSocketTCPEvent* event)
{
    switch (event->kind) {
        case PxSocketTCPAsync_Error: self->active = 0; break;

        case PxSocketTCPAsync_Connect: {
            if (event->connect.status != 0) {
                printf("[DEBUG] Connected!\n");

                u8*   buffer = pxMemoryArenaReserveManyOf(self->arena, u8, 256);
                ssize stop   = snprintf(((char*) buffer), 256, "Ciao!");

                pxAsyncIOQueueSubmit(self->queue, pxSocketTCPAsyncWrite(
                    self->arena, self, &clientOnSocketTCPEvent, self->socket, buffer, 0, stop));
            }
            else self->active = 0;
        } break;

        case PxSocketTCPAsync_Write: {
            printf("[DEBUG] Wrote message!\n");

            u8* buffer = pxMemoryArenaReserveManyOf(self->arena, u8, 256);

            pxAsyncIOQueueSubmit(self->queue, pxSocketTCPAsyncRead(
                self->arena, self, &clientOnSocketTCPEvent, self->socket, buffer, 0, 256));
        } break;

        case PxSocketTCPAsync_Read: {
            printf("[DEBUG] Read message!\n");

            u8*   values = event->read.values;
            ssize stop   = event->read.stop;

            printf("%.*s\n", ((int) stop), values);

            pxSocketTCPDestroy(self->socket);

            self->active = 0;
        } break;

        default: break;
    }
}

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxAddressIP address = pxAddressIPv4Local();
    u16         port    = 50000;

    ClientState client = {0};

    client.arena  = &arena;
    client.queue  = pxAsyncIOQueueReserve(&arena);
    client.socket = pxSocketTCPReserve(&arena);

    pxAsyncIOQueueCreate(client.queue);
    pxSocketTCPCreate(client.socket, pxAddressIPv4Empty(), 0);

    client.active = 1;

    pxAsyncIOQueueSubmit(client.queue, pxSocketTCPAsyncConnect(
        &arena, &client, &clientOnSocketTCPEvent, client.socket, address, port));

    for (ssize i = 0; i < 1000 && client.active != 0; i += 1)
        pxAsyncIOQueuePoll(client.queue, 10);

    pxSocketTCPDestroy(client.socket);
}
