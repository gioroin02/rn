#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/async/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/network/async/export.h"

#include <stdio.h>

typedef struct Server
{
    PxAsync*     async;
    PxSocketTcp* socket;

    b32 active;
}
Server;

void serverOnTcpEvent(Server* self, PxMemoryArena* arena, PxSocketTcpEvent event)
{
    if (event.kind == PxSocketTcpEvent_Error) self->active = 0;

    if (event.kind == PxSocketTcpEvent_Accept) {
        PxSocketTcp* value = event.accept.value;

        printf("[DEBUG] Accepted!\n");

        u8* buffer = pxMemoryArenaReserveManyOf(arena, u8, 256);

        pxSocketTcpReadAsync(self->async, PX_NULL,
            value, buffer, 0, sizeof buffer);

        PxSocketTcp* other = pxSocketTcpReserve(arena);

        pxSocketTcpAcceptAsync(self->async, PX_NULL,
            self->socket, other);
    }

    if (event.kind == PxSocketTcpEvent_Read) {
        PxSocketTcp* value = event.self;
        u8*          pntr  = event.read.pntr;
        ssize        stop  = event.read.stop;

        printf("[DEBUG] Read '%.*s'!\n", ((int) stop), pntr);

        pxSocketTcpWriteAsync(self->async, PX_NULL,
            value, pntr, 0, stop);
    }

    if (event.kind == PxSocketTcpEvent_Write) {
        printf("[DEBUG] Wrote!\n");

        pxSocketTcpDestroy(event.self);
    }
}

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMebi(2));

    PxAddressIp address = pxAddressIp4Local();
    u16         port    = 50000;

    Server server;

    server.async  = pxAsyncReserve(&arena);
    server.socket = pxSocketTcpReserve(&arena);
    server.active = 1;

    pxAsyncCreate(server.async, &arena, pxKibi(16));
    pxSocketTcpCreate(server.socket, address, port);
    pxSocketTcpBind(server.socket);
    pxSocketTcpListen(server.socket);

    PxSocketTcp* socket = pxSocketTcpReserve(&arena);

    pxSocketTcpAcceptAsync(server.async, PX_NULL,
        server.socket, socket);

    ssize index = 0;

    for (index = 0; index < 300; index += 1) {
        PxAsyncEventFamily family = PxAsyncEventFamily_None;

        u8 buffer[PX_SSIZE_KIBI];

        while (server.active != 0) {
            pxMemorySet(buffer, sizeof buffer, 0x00);

            family = pxAsyncPoll(server.async, 10, buffer, sizeof buffer);

            if (family == PxAsyncEventFamily_None) break;

            switch (family) {
                case PxAsyncEventFamily_Tcp:
                    serverOnTcpEvent(&server, &arena, *(PxSocketTcpEvent*) buffer);
                break;

                default: break;
            }
        }
    }

    pxSocketTcpDestroy(server.socket);
}
