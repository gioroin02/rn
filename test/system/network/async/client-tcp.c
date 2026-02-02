#include "../../../../src/rho-system/memory/export.h"
#include "../../../../src/rho-system/asyncio/export.h"
#include "../../../../src/rho-system/network/export.h"
#include "../../../../src/rho-system/network/async/export.h"

#include <stdio.h>

typedef struct Client
{
    RIoQueue*   queue;
    RSocketTcp* socket;

    RBool32 active;
}
Client;

void client_on_tcp_connect(Client* self, RMemoryArena* arena, RSocketTcpEventConnect event)
{
    if (event.status != 0) {
        printf("[DEBUG] Connected!\n");

        RInt size = 256;

        RUint8* buffer = rho_memory_arena_reserve_of(arena, RUint8, size);
        RInt    count  = snprintf((RChar8*) buffer, size, "%s", "Ciao");

        self->active = rho_socket_tcp_async_write(
            self->socket, buffer, 0, count, self->queue, NULL);
    }
    else self->active = 0;
}

void client_on_tcp_write(Client* self, RMemoryArena* arena, RSocketTcpEventWrite event)
{
    RInt size = 256;

    RUint8* buffer = rho_memory_arena_reserve_of(arena, RUint8, size);

    self->active = rho_socket_tcp_async_read(
        event.socket, buffer, 0, size, self->queue, NULL);

    printf("[DEBUG] Wrote!\n");
}

void client_on_tcp_read(Client* self, RMemoryArena* arena, RSocketTcpEventRead event)
{
    printf("[DEBUG] Read '%.*s'!\n", ((int) event.bytes), event.pntr + event.start);

    self->active = 0;
}

int main(int argc, char** argv)
{
    RMemoryArena arena = rho_system_memory_reserve(rho_memory_mib(2));

    Client client = {0};

    client.queue  = rho_io_queue_reserve(&arena);
    client.socket = rho_socket_tcp_reserve(&arena);

    RMemoryPool pool = rho_memory_pool_make(
        rho_memory_arena_reserve_of(&arena, RUint8, rho_memory_kib(16)),
        rho_memory_kib(16), 512);

    rho_io_queue_create(client.queue, pool);
    rho_socket_tcp_create(client.socket, rho_host_ip_make(rho_address_ip4_any(), 0));

    client.active = 1;

    RHostIp host = rho_host_ip_make(rho_address_ip4_self(), 50000);

    client.active = rho_socket_tcp_async_connect(client.socket, host, client.queue, NULL);

    while (client.active != 0) {
        void*     marker = rho_memory_arena_tell(&arena);
        RIoEvent* event  = rho_io_queue_poll_event(client.queue, 10, &arena);

        if (event == NULL || event->family == RIoEventFamily_None) continue;

        switch (event->family) {
            case RIoEventFamily_Tcp: {
                RSocketTcpEvent event_tcp = *(RSocketTcpEvent*) event;

                rho_memory_arena_rewind(&arena, marker);

                switch (event_tcp.kind) {
                    case RSocketTcpEvent_Connect: client_on_tcp_connect(&client, &arena, event_tcp.connect); break;
                    case RSocketTcpEvent_Write:   client_on_tcp_write(&client, &arena, event_tcp.write); break;
                    case RSocketTcpEvent_Read:    client_on_tcp_read(&client, &arena, event_tcp.read); break;

                    default: break;
                }
            } break;

            default: break;
        }
    }

    rho_socket_tcp_destroy(client.socket);
    rho_io_queue_destroy(client.queue);
}
