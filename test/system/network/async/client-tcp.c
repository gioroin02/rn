#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/asyncio/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/network/async/export.h"

#include <stdio.h>

typedef struct Client
{
    PAsyncIoQueue* queue;
    PSocketTcp*    socket;

    B32 active;
}
Client;

void clientOnTcpConnect(Client* self, PMemoryArena* arena, PSocketTcpEventConnect event)
{
    if (event.status != 0) {
        printf("[DEBUG] Connected!\n");

        U8* buffer = pMemoryArenaReserveManyOf(arena, U8, 256);
        Int count  = snprintf((I8*) buffer, 256, "%s", "Ciao");

        self->active = pSocketTcpWriteAsync(
            self->socket, buffer, 0, count, self->queue, NULL);
    }
    else self->active = 0;
}

void clientOnTcpWrite(Client* self, PMemoryArena* arena, PSocketTcpEventWrite event)
{
    U8* buffer = pMemoryArenaReserveManyOf(arena, U8, 256);

    self->active = pSocketTcpReadAsync(
        event.socket, buffer, 0, 256, self->queue, NULL);

    printf("[DEBUG] Wrote!\n");
}

void clientOnTcpRead(Client* self, PMemoryArena* arena, PSocketTcpEventRead event)
{
    printf("[DEBUG] Read '%.*s'!\n", ((int) event.bytes), event.pntr + event.start);

    self->active = 0;
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    Client client;

    client.queue  = pAsyncIoQueueReserve(&arena);
    client.socket = pSocketTcpReserve(&arena);

    PMemoryPool pool = pMemoryPoolMake(
        pMemoryArenaReserveManyOf(&arena, U8, pMemoryKIB(16)),
        pMemoryKIB(16), 512);

    pAsyncIoQueueCreate(client.queue, pool);
    pSocketTcpCreate(client.socket, pHostIpMake(pAddressIp4Any(), 0));

    client.active = 1;

    PHostIp server = pHostIpMake(pAddressIp4Self(), 50000);

    client.active = pSocketTcpConnectAsync(client.socket, server, client.queue, NULL);

    while (client.active != 0) {
        void*             marker = pMemoryArenaTell(&arena);
        PAsyncIoEvent*    event  = NULL;
        PAsyncIoEventKind kind   = pAsyncIoQueuePollEvent(client.queue, 10, &arena, &event);

        if (kind == PAsyncIoEvent_None) continue;

        switch (kind) {
            case PAsyncIoEvent_Tcp: {
                PSocketTcpEvent event_tcp = *(PSocketTcpEvent*) event;

                pMemoryArenaRewind(&arena, marker);

                switch (event_tcp.kind) {
                    case PSocketTcpEvent_Connect: clientOnTcpConnect(&client, &arena, event_tcp.connect); break;
                    case PSocketTcpEvent_Write:   clientOnTcpWrite(&client, &arena, event_tcp.write); break;
                    case PSocketTcpEvent_Read:    clientOnTcpRead(&client, &arena, event_tcp.read); break;

                    default: break;
                }
            } break;

            default: break;
        }
    }

    pSocketTcpDestroy(client.socket);
    pAsyncIoQueueDestroy(client.queue);
}
