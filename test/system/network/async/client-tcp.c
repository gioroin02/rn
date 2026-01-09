#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/async/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/network/async/export.h"

#include <stdio.h>

typedef struct Client
{
    PxAsync*     async;
    PxSocketTcp* socket;

    b32 active;
}
Client;

void clientOnTcpEvent(Client* self, PxMemoryArena* arena, PxSocketTcpEvent event)
{
    switch (event.kind) {
        case PxSocketTcpEvent_Error: self->active = 0; break;

        case PxSocketTcpEvent_Connect: {
            if (event.connect.status != 0) {
                printf("[DEBUG] Connected!\n");

                u8*   buffer = pxMemoryArenaReserveManyOf(arena, u8, 256);
                ssize stop   = snprintf(((char*) buffer), 256, "%s", "Ciao");

                pxSocketTcpWriteAsync(self->async, PX_NULL,
                    self->socket, buffer, 0, stop);
            }
            else self->active = 0;
        } break;

        case PxSocketTcpEvent_Write: {
            u8* buffer = pxMemoryArenaReserveManyOf(arena, u8, 256);

            pxSocketTcpReadAsync(self->async, PX_NULL,
                self->socket, buffer, 0, 256);

            printf("[DEBUG] Wrote!\n");
        } break;

        case PxSocketTcpEvent_Read: {
            u8*   pntr = event.read.pntr;
            ssize stop = event.read.stop;

            printf("[DEBUG] Read '%.*s'!\n", ((int) stop), pntr);

            pxSocketTcpDestroy(self->socket);

            self->active = 0;
        } break;

        default: break;
    }
}

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(2));

    PxAddressIp address = pxAddressIp4Local();
    u16         port    = 50000;

    Client client;

    client.async  = pxAsyncReserve(&arena);
    client.socket = pxSocketTcpReserve(&arena);

    pxAsyncCreate(client.async, &arena, pxMemoryKIB(16));
    pxSocketTcpCreate(client.socket, pxAddressIp4Empty(), 0);

    client.active = 1;

    pxSocketTcpConnectAsync(client.async, PX_NULL,
        client.socket, address, port);

    ssize index = 0;

    for (index = 0; index < 500; index += 1) {
        PxAsyncEventFamily family = PxAsyncEventFamily_None;

        u8 buffer[PX_MEMORY_KIB];

        while (client.active != 0) {
            pxMemorySet(buffer, sizeof buffer, 0x00);

            family = pxAsyncPoll(client.async, 10, buffer, sizeof buffer);

            if (family == PxAsyncEventFamily_None) break;

            switch (family) {
                case PxAsyncEventFamily_Tcp:
                    clientOnTcpEvent(&client, &arena, *(PxSocketTcpEvent*) buffer);
                break;

                default: break;
            }
        }
    }

    pxSocketTcpDestroy(client.socket);
}
