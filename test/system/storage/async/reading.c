#include "../../../../src/base/string/export.h"
#include "../../../../src/system/memory/export.h"
#include "../../../../src/system/asyncio/export.h"
#include "../../../../src/system/storage/export.h"
#include "../../../../src/system/storage/async/export.h"

#include <stdio.h>

typedef struct Reader
{
    PAsyncIoQueue* queue;
    PFile*         file;

    B32 active;
}
Reader;

void readerOnFileRead(Reader* self, PMemoryArena* arena, PFileEventRead event)
{
    if (event.bytes != 0) {
        printf("[DEBUG] Read '%.*s'!\n", (int) event.bytes, event.pntr + event.start);

        self->active = pFileReadAsync(event.file, event.pntr,
            event.start, event.bytes, self->queue, NULL);
    }
    else printf("[DEBUG] Done reading!\n");
}

int main(int argc, char** argv)
{
    PString8 name = pString8("README.md");

    if (argc >= 2) {
        name.values = (U8*) argv[1];
        name.size   = 0;

        for (Int i = 0; i < 4096 && name.size == 0; i += 1) {
            if (name.values[i] == 0)
                name.size = i + 1;
        }
    }

    PMemoryArena arena = pSystemMemoryReserve(pMemoryMIB(2));

    Reader reader = {0};

    reader.queue = pAsyncIoQueueReserve(&arena);
    reader.file  = pFileReserve(&arena);

    PMemoryPool pool = pMemoryPoolMake(
        pMemoryArenaReserveManyOf(&arena, U8, pMemoryKIB(16)),
        pMemoryKIB(16), 512);

    pAsyncIoQueueCreate(reader.queue, pool);
    pFileOpen(reader.file, name, PFileMode_Read);

    U8* buffer = pMemoryArenaReserveManyOf(&arena, U8, 256);

    reader.active = pFileReadAsync(reader.file,
        buffer, 0, 256, reader.queue, NULL);

    while (reader.active != 0) {
        void* marker = pMemoryArenaTell(&arena);

        PAsyncIoEvent*    event  = NULL;
        PAsyncIoEventKind kind   = pAsyncIoQueuePollEvent(reader.queue, 10, &arena, &event);

        if (kind == PAsyncIoEvent_None) continue;

        switch (kind) {
            case PAsyncIoEvent_Tcp: {
                PFileEvent event_file = *(PFileEvent*) event;

                pMemoryArenaRewind(&arena, marker);

                switch (event_file.kind) {
                    case PFileEvent_Read:
                        readerOnFileRead(&reader, &arena, event_file.read);
                    break;

                    default: break;
                }
            } break;

            default: break;
        }
    }

    pFileClose(reader.file);
    pAsyncIoQueueDestroy(reader.queue);
}
