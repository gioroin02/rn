#include "../../../../src/base/export.h"

#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/async/export.h"
#include "../../../../src/system/async/network/export.h"

#include <stdio.h>
#include <string.h>

typedef struct Client
{
    PxAsync*     async;
    PxSocketTcp* socket;

    b32 active;
}
Client;

void
clientOnSocketTcpEvent(Client* self, PxMemoryArena* arena, PxSocketTcpEvent* event)
{
    switch (event->kind) {
        case PxSocketTcpEvent_Error: self->active = 0; break;

        case PxSocketTcpEvent_Connect: {
            if (event->connect.status != 0) {
                printf("[DEBUG] Connected!\n");

                u8*   buffer = pxMemoryArenaReserveManyOf(arena, u8, 256);
                ssize stop   = snprintf(((char*) buffer), 256, "Ciao!");

                pxSocketTcpWriteAsync(self->async, self->socket, buffer, 0, stop);
            }
            else self->active = 0;
        } break;

        case PxSocketTcpEvent_Write: {
            u8* buffer = pxMemoryArenaReserveManyOf(arena, u8, 256);

            pxSocketTcpReadAsync(self->async, self->socket, buffer, 0, 256);
        } break;

        case PxSocketTcpEvent_Read: {
            u8*   values = event->read.values;
            ssize stop   = event->read.stop;

            printf("%.*s\n", ((int) stop), values);

            pxSocketTcpDestroy(self->socket);

            self->active = 0;
        } break;

        default: break;
    }
}

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxAddressIp address = pxAddressIp4Local();
    u16         port    = 50000;

    Client client = {0};

    client.async  = pxAsyncReserve(&arena);
    client.socket = pxSocketTcpReserve(&arena);

    pxAsyncCreate(client.async, &arena, pxMemoryKiB(16));
    pxSocketTcpCreate(client.socket, pxAddressIp4Empty(), 0);

    client.active = 1;

    pxSocketTcpConnectAsync(client.async, client.socket, address, port);

    ssize index = 0;

    for (index = 0; index < 1000 && client.active != 0; index += 1) {
        PxAsyncEventFamily family = PxAsyncEventFamily_None;
        void*              event  = PX_NULL;

        do {
            family = pxAsyncPoll(client.async, &event, 10);

            if (family == PxAsyncEventFamily_Tcp)
                clientOnSocketTcpEvent(&client, &arena, event);

            pxAsyncReturn(&client.async, event);
        }
        while (family != PxAsyncEventFamily_None);
    }

    pxSocketTcpDestroy(client.socket);
}
