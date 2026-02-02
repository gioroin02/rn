#include "../../../../src/rho-base/string/export.h"
#include "../../../../src/rho-system/memory/export.h"
#include "../../../../src/rho-system/asyncio/export.h"
#include "../../../../src/rho-system/storage/export.h"
#include "../../../../src/rho-system/storage/async/export.h"

#include <stdio.h>

typedef struct Reader
{
    RIoQueue* queue;
    RFile*    file;

    RBool32 active;
}
Reader;

void reader_on_file_read(Reader* self, RMemoryArena* arena, RFileEventRead event)
{
    if (event.bytes != 0) {
        printf("[DEBUG] Read '%.*s'!\n", (int) event.bytes, event.pntr + event.start);

        self->active = rho_file_async_read(event.file, event.pntr,
            event.start, event.bytes, self->queue, NULL);
    }
    else printf("[DEBUG] Done reading!\n");
}

int main(int argc, char** argv)
{
    RString8 name = rho_string8("README.md");

    if (argc >= 2) {
        name.values = (RChar8*) argv[1];
        name.size   = 0;

        for (RInt i = 0; i < 4096 && name.size == 0; i += 1) {
            if (name.values[i] == 0)
                name.size = i + 1;
        }
    }

    RMemoryArena arena = rho_system_memory_reserve(rho_memory_mib(2));

    Reader reader = {0};

    reader.queue = rho_io_queue_reserve(&arena);
    reader.file  = rho_file_reserve(&arena);

    RMemoryPool pool = rho_memory_pool_make(
        rho_memory_arena_reserve_of(&arena, RUint8, rho_memory_kib(16)),
        rho_memory_kib(16), 512);

    rho_io_queue_create(reader.queue, pool);
    rho_file_open(reader.file, name, RFileMode_Read);

    RUint8* buffer = rho_memory_arena_reserve_of(&arena, RUint8, 256);

    reader.active = rho_file_async_read(reader.file,
        buffer, 0, 256, reader.queue, NULL);

    while (reader.active != 0) {
        void*     marker = rho_memory_arena_tell(&arena);
        RIoEvent* event  = rho_io_queue_poll_event(reader.queue, 10, &arena);

        if (event == NULL || event->family == RIoEventFamily_None) continue;

        switch (event->family) {
            case RIoEventFamily_File: {
                RFileEvent event_file = *(RFileEvent*) event;

                rho_memory_arena_rewind(&arena, marker);

                switch (event_file.kind) {
                    case RFileEvent_Read:
                        reader_on_file_read(&reader, &arena, event_file.read);
                    break;

                    default: break;
                }
            } break;

            default: break;
        }
    }

    rho_file_close(reader.file);
    rho_io_queue_destroy(reader.queue);
}
