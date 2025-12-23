#include "../../../../src/base/memory/export.h"

#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/async/export.h"
#include "../../../../src/system/async/network/export.h"

#include <stdio.h>

typedef enum PxAsyncEventKind
{
    PxAsyncEvent_None,
    PxAsyncEvent_SocketTcp,
    PxAsyncEvent_SocketUdp,
    PxAsyncEvent_File,
    PxAsyncEvent_Terminal,
}
PxAsyncEventKind;

typedef struct ServerState
{
    PxAsync*     async;
    PxSocketTcp* socket;

    b32 active;
}
ServerState;

void
serverOnSocketTcpEvent(ServerState* self, PxMemoryArena* arena, PxSocketTcpEvent* event)
{
    if (event->kind == PxSocketTcpEvent_Error) self->active = 0;

    if (event->kind == PxSocketTcpEvent_Accept) {
        PxSocketTcp* socket = event->accept.socket;

        printf("[DEBUG] Connected!\n");

        u8* buffer = pxMemoryArenaReserveManyOf(arena, u8, 256);

        pxSocketTcpReadAsync(self->async, arena,
            PxAsyncEvent_SocketTcp, socket, buffer, 0, 256);

        PxSocketTcp* other = pxSocketTcpReserve(arena);

        pxSocketTcpAcceptAsync(self->async, arena,
            PxAsyncEvent_SocketTcp, self->socket, other);
    }

    if (event->kind == PxSocketTcpEvent_Read) {
        PxSocketTcp* socket = event->read.socket;
        u8*          values = event->read.values;
        ssize        stop   = event->read.stop;

        printf("%.*s\n", ((int) stop), values);

        pxSocketTcpWriteAsync(self->async, arena,
            PxAsyncEvent_SocketTcp, socket, values, 0, stop);
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

    ServerState server = {0};

    server.async  = pxAsyncReserve(&arena);
    server.socket = pxSocketTcpReserve(&arena);

    pxAsyncCreate(server.async);
    pxSocketTcpCreate(server.socket, address, port);
    pxSocketTcpBind(server.socket);
    pxSocketTcpListen(server.socket);

    server.active = 1;

    PxSocketTcp* socket = pxSocketTcpReserve(&arena);

    pxSocketTcpAcceptAsync(server.async, &arena,
        PxAsyncEvent_SocketTcp, server.socket, socket);

    ssize index = 0;

    for (index = 0; index < 1000 && server.active != 0; index += 1) {
        void* event = PX_NULL;
        ssize kind  = 0;

        while (kind >= 0) {
            kind = pxAsyncPoll(server.async, &event, 10);

            if (kind == PxAsyncEvent_SocketTcp)
                serverOnSocketTcpEvent(&server, &arena, event);
        }
    }

    pxSocketTcpDestroy(server.socket);
}
