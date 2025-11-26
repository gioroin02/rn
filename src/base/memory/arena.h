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
rn_memory_arena_make(void* memory, ssize size);

void
rn_memory_arena_clear(RnMemoryArena* self);

void*
rn_memory_arena_tell(RnMemoryArena* self);

RnMemorySlice
rn_memory_arena_reserve_slice(RnMemoryArena* self, ssize amount, ssize step);

b32
rn_memory_arena_release_slice(RnMemoryArena* self, RnMemorySlice value);

#endif // RN_BASE_MEMORY_ARENA_H
