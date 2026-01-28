#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/asyncio/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/network/async/export.h"

#include <stdio.h>

typedef struct Server
{
    PAsyncIoQueue* queue;
    PSocketTcp*    socket;

    B32 active;
}
Server;

void serverOnTcpAccept(Server* self, PMemoryArena* arena, PSocketTcpEventAccept event)
{
    printf("[DEBUG] Accepted!\n");

    U8* buffer = pMemoryArenaReserveManyOf(arena, U8, 256);

    self->active = pSocketTcpReadAsync(
        event.value, buffer, 0, sizeof buffer, self->queue, NULL);

    PSocketTcp* other = pSocketTcpReserve(arena);

    if (other != NULL) {
        self->active = pSocketTcpAcceptAsync(
            self->socket, other, self->queue, NULL);
    }
    else self->active = 0;
}

void serverOnTcpWrite(Server* self, PMemoryArena* arena, PSocketTcpEventWrite event)
{
    printf("[DEBUG] Wrote!\n");

    pSocketTcpDestroy(event.socket);
}

void serverOnTcpRead(Server* self, PMemoryArena* arena, PSocketTcpEventRead event)
{
    printf("[DEBUG] Read '%.*s'!\n", (int) event.bytes, event.pntr + event.start);

    self->active = pSocketTcpWriteAsync(event.socket, event.pntr,
        event.start, event.bytes, self->queue, NULL);
}

int main(int argc, char** argv)
{
    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    Server server = {0};

    server.queue  = pAsyncIoQueueReserve(&arena);
    server.socket = pSocketTcpReserve(&arena);

    PMemoryPool pool = pMemoryPoolMake(
        pMemoryArenaReserveManyOf(&arena, U8, pMemoryKIB(16)),
        pMemoryKIB(16), 512);

    pAsyncIoQueueCreate(server.queue, pool);

    pSocketTcpCreate(server.socket, pHostIpMake(pAddressIp4Self(), 50000));
    pSocketTcpBind(server.socket);
    pSocketTcpListen(server.socket);

    server.active = 1;

    PSocketTcp* other = pSocketTcpReserve(&arena);

    server.active = pSocketTcpAcceptAsync(server.socket, other, server.queue, NULL);

    while (server.active != 0) {
        void*             marker = pMemoryArenaTell(&arena);
        PAsyncIoEvent*    event  = NULL;
        PAsyncIoEventKind kind   = pAsyncIoQueuePollEvent(server.queue, 10, &arena, &event);

        if (kind == PAsyncIoEvent_None) continue;

        switch (kind) {
            case PAsyncIoEvent_Tcp: {
                PSocketTcpEvent event_tcp = *(PSocketTcpEvent*) event;

                pMemoryArenaRewind(&arena, marker);

                switch (event_tcp.kind) {
                    case PSocketTcpEvent_Accept: serverOnTcpAccept(&server, &arena, event_tcp.accept); break;
                    case PSocketTcpEvent_Write:  serverOnTcpWrite(&server, &arena, event_tcp.write); break;
                    case PSocketTcpEvent_Read:   serverOnTcpRead(&server, &arena, event_tcp.read); break;

                    default: break;
                }
            } break;

            default: break;
        }
    }

    pSocketTcpDestroy(server.socket);
    pAsyncIoQueueDestroy(server.queue);
}
