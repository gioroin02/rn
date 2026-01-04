#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/async/export.h"
#include "../../../../src/system/async/network/export.h"

#include <stdio.h>

typedef struct Server
{
    PxAsync*     async;
    PxSocketTcp* socket;

    b32 active;
}
Server;

void
serverOnTcpEvent(Server* self, PxMemoryArena* arena, PxSocketTcpEvent event)
{
    if (event.kind == PxSocketTcpEvent_Error) self->active = 0;

    if (event.kind == PxSocketTcpEvent_Accept) {
        PxSocketTcp* socket = event.accept.socket;

        printf("[DEBUG] Accepted!\n");

        u8* buffer = pxMemoryArenaReserveManyOf(arena, u8, 256);

        pxSocketTcpReadAsync(self->async, PX_NULL,
            socket, buffer, 0, sizeof buffer);

        PxSocketTcp* other = pxSocketTcpReserve(arena);

        pxSocketTcpAcceptAsync(self->async, PX_NULL,
            self->socket, other);
    }

    if (event.kind == PxSocketTcpEvent_Read) {
        PxSocketTcp* socket = event.read.socket;
        u8*          values = event.read.values;
        ssize        stop   = event.read.stop;

        printf("[DEBUG] Read '%.*s'!\n", ((int) stop), values);

        pxSocketTcpWriteAsync(self->async, PX_NULL,
            socket, values, 0, stop);
    }

    if (event.kind == PxSocketTcpEvent_Write) {
        printf("[DEBUG] Wrote!\n");

        pxSocketTcpDestroy(event.write.socket);
    }
}

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxAddressIp address = pxAddressIp4Local();
    u16         port    = 50000;

    Server server;

    server.async  = pxAsyncReserve(&arena);
    server.socket = pxSocketTcpReserve(&arena);
    server.active = 1;

    pxAsyncCreate(server.async, &arena, pxMemoryKiB(16));
    pxSocketTcpCreate(server.socket, address, port);
    pxSocketTcpBind(server.socket);
    pxSocketTcpListen(server.socket);

    PxSocketTcp* socket = pxSocketTcpReserve(&arena);

    pxSocketTcpAcceptAsync(server.async, PX_NULL,
        server.socket, socket);

    ssize index = 0;

    for (index = 0; index < 500; index += 1) {
        PxAsyncEventFamily family = PxAsyncEventFamily_None;

        while (server.active != 0) {
            void* event = PX_NULL;

            family = pxAsyncPoll(server.async, PX_NULL, &event, 10);

            if (family == PxAsyncEventFamily_None) break;

            switch (family) {
                case PxAsyncEventFamily_Tcp: {
                    PxSocketTcpEvent tcp;

                    pxAsyncReturn(server.async, event, &tcp, sizeof tcp);

                    serverOnTcpEvent(&server, &arena, tcp);
                } break;

                default: break;
            }
        }
    }

    pxSocketTcpDestroy(server.socket);
}
