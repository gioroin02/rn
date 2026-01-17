#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/asyncio/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/network/async/export.h"

#include <stdio.h>

typedef struct Client
{
    PMemoryArena* arena;

    PAsyncIoQueue* queue;
    PSocketTcp*    socket;

    B32 active;
}
Client;

void clientOnTcpConnect(Client* self, PSocketTcp* socket, PHostIp host, Bool status);

void clientOnTcpWrite(Client* self, PSocketTcp* socket, U8* pntr, Int start, Int stop, Int bytes);

void clientOnTcpRead(Client* self, PSocketTcp* socket, U8* pntr, Int start, Int stop, Int bytes);

void clientOnTcpConnect(Client* self, PSocketTcp* socket, PHostIp host, Bool status)
{
    if (status != 0) {
        printf("[DEBUG] Connected!\n");

        U8* buffer = pMemoryArenaReserveManyOf(self->arena, U8, 256);
        Int stop   = snprintf((I8*) buffer, 256, "%s", "Ciao");

        self->active = pSocketTcpWriteAsync(socket, buffer, 0, stop,
            self->queue, self, clientOnTcpWrite);
    }
    else self->active = 0;
}

void clientOnTcpWrite(Client* self, PSocketTcp* socket, U8* pntr, Int start, Int stop, Int bytes)
{
    U8* buffer = pMemoryArenaReserveManyOf(self->arena, U8, 256);

    self->active = pSocketTcpReadAsync(socket, buffer, 0, 256,
        self->queue, self, clientOnTcpRead);

    printf("[DEBUG] Wrote!\n");
}

void clientOnTcpRead(Client* self, PSocketTcp* socket, U8* pntr, Int start, Int stop, Int bytes)
{
    printf("[DEBUG] Read '%.*s'!\n", ((int) bytes), pntr + start);

    pSocketTcpDestroy(self->socket);
    pAsyncIoQueueDestroy(self->queue);

    self->active = 0;
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    Client client;

    client.arena  = &arena;
    client.queue  = pAsyncIoQueueReserve(&arena);
    client.socket = pSocketTcpReserve(&arena);

    PMemoryPool pool = pMemoryPoolMake(
        pMemoryArenaReserveManyOf(&arena, U8, pMemoryKIB(16)),
        pMemoryKIB(16), 512);

    pAsyncIoQueueCreate(client.queue, pool);
    pSocketTcpCreate(client.socket, pHostIpMake(pAddressIp4Any(), 0));

    client.active = 1;

    PHostIp server = pHostIpMake(pAddressIp4Self(), 50000);

    client.active = pSocketTcpConnectAsync(client.socket, server,
        client.queue, &client, clientOnTcpConnect);

    while (client.active != 0)
        pAsyncIoQueuePollEvents(client.queue, 10);

    pSocketTcpDestroy(client.socket);
}
