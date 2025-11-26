#ifndef RN_BASE_MEMORY_ARENA_H
#define RN_BASE_MEMORY_ARENA_H

#include "./slice.h"

typedef struct RnMemoryArena
{
    u8*   values;
    ssize size;
    ssize count;
}
RnMemoryArena;

RnMemoryArena
rnMemoryArenaMake(void* memory, ssize size);

void
rnMemoryArenaClear(RnMemoryArena* self);

void*
rnMemoryArenaTell(RnMemoryArena* self);

RnMemorySlice
rnMemoryArenaReserveSlice(RnMemoryArena* self, ssize amount, ssize step);

b32
rnMemoryArenaReleaseSlice(RnMemoryArena* self, RnMemorySlice value);

#endif // RN_BASE_MEMORY_ARENA_H
