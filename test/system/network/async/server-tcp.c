#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/asyncio/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/network/async/export.h"

#include <stdio.h>

typedef struct Server
{
    PMemoryArena* arena;

    PAsyncIoQueue* queue;
    PSocketTcp*    socket;

    B32 active;
}
Server;

void serverOnTcpAccept(Server* self, PSocketTcp* socket, PSocketTcp* value);

void serverOnTcpWrite(Server* self, PSocketTcp* socket, U8* pntr, Int start, Int stop, Int bytes);

void serverOnTcpRead(Server* self, PSocketTcp* socket, U8* pntr, Int start, Int stop, Int bytes);

void serverOnTcpAccept(Server* self, PSocketTcp* socket, PSocketTcp* value)
{
    printf("[DEBUG] Accepted!\n");

    U8* buffer = pMemoryArenaReserveManyOf(self->arena, U8, 256);

    self->active = pSocketTcpReadAsync(value, buffer, 0, sizeof buffer,
        self->queue, self, serverOnTcpRead);

    PSocketTcp* other = pSocketTcpReserve(self->arena);

    if (other != NULL) {
        self->active = pSocketTcpAcceptAsync(self->socket, other,
            self->queue, self, serverOnTcpAccept);
    }
    else self->active = 0;
}

void serverOnTcpWrite(Server* self, PSocketTcp* socket, U8* pntr, Int start, Int stop, Int bytes)
{
    printf("[DEBUG] Wrote!\n");

    pSocketTcpDestroy(socket);
}

void serverOnTcpRead(Server* self, PSocketTcp* socket, U8* pntr, Int start, Int stop, Int bytes)
{
    printf("[DEBUG] Read '%.*s'!\n", ((int) bytes), pntr + start);

    self->active = pSocketTcpWriteAsync(socket, pntr, start, bytes,
        self->queue, self, serverOnTcpWrite);
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    Server server;

    server.arena  = &arena;
    server.queue  = pAsyncIoQueueReserve(&arena);
    server.socket = pSocketTcpReserve(&arena);

    PMemoryPool pool = pMemoryPoolMake(
        pMemoryArenaReserveManyOf(&arena, U8, pMemoryKIB(16)),
        pMemoryKIB(16), 512);

    pAsyncIoQueueCreate(server.queue, pool);

    pSocketTcpCreate(server.socket, pHostIpMake(pAddressIp4Self(), 50000));
    pSocketTcpBind(server.socket);
    pSocketTcpListen(server.socket);

    PSocketTcp* socket = pSocketTcpReserve(&arena);

    server.active = 1;

    server.active = pSocketTcpAcceptAsync(server.socket, socket,
        server.queue, &server, serverOnTcpAccept);

    while (server.active != 0)
        pAsyncIoQueuePollEvents(server.queue, 10);

    pSocketTcpDestroy(server.socket);
}
