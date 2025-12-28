#include "../../../../src/base/memory/export.h"

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
serverOnSocketTcpEvent(Server* self, PxMemoryArena* arena, PxSocketTcpEvent* event)
{
    if (event->kind == PxSocketTcpEvent_Error) self->active = 0;

    if (event->kind == PxSocketTcpEvent_Accept) {
        PxSocketTcp* socket = event->accept.socket;

        printf("[DEBUG] Connected!\n");

        u8* buffer = pxMemoryArenaReserveManyOf(arena, u8, 256);

        pxSocketTcpReadAsync(self->async, socket, buffer, 0, 256);

        PxSocketTcp* other = pxSocketTcpReserve(arena);

        pxSocketTcpAcceptAsync(self->async, self->socket, other);
    }

    if (event->kind == PxSocketTcpEvent_Read) {
        PxSocketTcp* socket = event->read.socket;
        u8*          values = event->read.values;
        ssize        stop   = event->read.stop;

        printf("%.*s\n", ((int) stop), values);

        pxSocketTcpWriteAsync(self->async, socket, values, 0, stop);
    }

    if (event->kind == PxSocketTcpEvent_Write)
        pxSocketTcpDestroy(event->write.socket);
}

int
main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMiB(2));

    PxAddressIp address = pxAddressIp4Local();
    u16         port    = 50000;

    Server server = {0};

    server.async  = pxAsyncReserve(&arena);
    server.socket = pxSocketTcpReserve(&arena);

    pxAsyncCreate(server.async, &arena, pxMemoryKiB(16));
    pxSocketTcpCreate(server.socket, address, port);
    pxSocketTcpBind(server.socket);
    pxSocketTcpListen(server.socket);

    server.active = 1;

    PxSocketTcp* socket = pxSocketTcpReserve(&arena);

    pxSocketTcpAcceptAsync(server.async, server.socket, socket);

    ssize index = 0;

    for (index = 0; index < 1000 && server.active != 0; index += 1) {
        PxAsyncEventFamily family = PxAsyncEventFamily_None;
        void*              event  = PX_NULL;

        do {
            family = pxAsyncPoll(server.async, &event, 10);

            if (family == PxAsyncEventFamily_Tcp)
                serverOnSocketTcpEvent(&server, &arena, event);

            pxAsyncReturn(&server.async, event);
        }
        while (family != PxAsyncEventFamily_None);
    }

    pxSocketTcpDestroy(server.socket);
}
