#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/asyncio/export.h"
#include "../../../../src/system/network/export.h"
#include "../../../../src/system/network/async/export.h"

#include <stdio.h>

typedef struct Server
{
    RIoQueue*   queue;
    RSocketTcp* socket;

    RBool32 active;
}
Server;

void server_on_tcp_accept(Server* self, RMemoryArena* arena, RSocketTcpEventAccept event)
{
    printf("[DEBUG] Accepted!\n");

    RInt size = 256;

    RUint8* buffer = rho_memory_arena_reserve_of(arena, RUint8, size);

    self->active = rho_socket_tcp_async_read(
        event.value, buffer, 0, size, self->queue, NULL);

    RSocketTcp* other = rho_socket_tcp_reserve(arena);

    if (other != NULL) {
        self->active = rho_socket_tcp_async_accept(
            self->socket, other, self->queue, NULL);
    }
    else self->active = 0;
}

void server_on_tcp_write(Server* self, RMemoryArena* arena, RSocketTcpEventWrite event)
{
    printf("[DEBUG] Wrote!\n");

    rho_socket_tcp_destroy(event.socket);
}

void server_on_tcp_read(Server* self, RMemoryArena* arena, RSocketTcpEventRead event)
{
    printf("[DEBUG] Read '%.*s'!\n", (int) event.bytes, event.pntr + event.start);

    self->active = rho_socket_tcp_async_write(event.socket, event.pntr,
        event.start, event.bytes, self->queue, NULL);
}

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(rho_memory_mib(2));

    Server server = {0};

    server.queue  = rho_io_queue_reserve(&arena);
    server.socket = rho_socket_tcp_reserve(&arena);

    RMemoryPool pool = rho_memory_pool_make(
        rho_memory_arena_reserve_of(&arena, RUint8, rho_memory_kib(16)),
        rho_memory_kib(16), 512);

    rho_io_queue_create(server.queue, pool);

    rho_socket_tcp_create(server.socket, rho_host_ip_make(rho_address_ip4_self(), 50000));

    rho_socket_tcp_bind(server.socket);
    rho_socket_tcp_listen(server.socket);

    server.active = 1;

    RSocketTcp* other = rho_socket_tcp_reserve(&arena);

    server.active = rho_socket_tcp_async_accept(server.socket, other, server.queue, NULL);

    while (server.active != 0) {
        void*     marker = rho_memory_arena_tell(&arena);
        RIoEvent* event  = rho_io_queue_poll_event(server.queue, 10, &arena);

        if (event == NULL || event->family == RIoEventFamily_None) continue;

        switch (event->family) {
            case RIoEventFamily_Tcp: {
                RSocketTcpEvent event_tcp = *(RSocketTcpEvent*) event;

                rho_memory_arena_rewind(&arena, marker);

                switch (event_tcp.kind) {
                    case RSocketTcpEvent_Accept: server_on_tcp_accept(&server, &arena, event_tcp.accept); break;
                    case RSocketTcpEvent_Write:  server_on_tcp_write(&server, &arena, event_tcp.write); break;
                    case RSocketTcpEvent_Read:   server_on_tcp_read(&server, &arena, event_tcp.read); break;

                    default: break;
                }
            } break;

            default: break;
        }
    }

    rho_socket_tcp_destroy(server.socket);
    rho_io_queue_destroy(server.queue);
}
