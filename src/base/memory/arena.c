#ifndef RN_BASE_MEMORY_ARENA_C
#define RN_BASE_MEMORY_ARENA_C

#include "./arena.h"

RnMemoryArena
rnMemoryArenaMake(void* memory, ssize size)
{
    RnMemoryArena result = {0};

    if (memory == 0 || size <= 0)
        return result;

    result.values = ((u8*) memory);
    result.size   = size;

    return result;
}

void
rnMemoryArenaClear(RnMemoryArena* self)
{
    self->count = 0;
}

void*
rnMemoryArenaTell(RnMemoryArena* self)
{
    return self->values + self->count;
}

RnMemorySlice
rnMemoryArenaReserveSlice(RnMemoryArena* self, ssize amount, ssize step)
{
    RnMemorySlice result = {0};

    if (amount <= 0 || step <= 0 || amount > RN_MAX_SSIZE / step)
        return result;

    ssize size   = amount * step;
    void* memory = rnMemoryArenaTell(self);

    if (self->count < 0 || self->count + size > self->size)
        return result;

    result = rnMemorySliceMake(memory, 0, amount, step);

    rnMemorySliceZero(result);

    self->count = rnMemoryAlignForward(
        self->count + size, RN_MEMORY_DEFAULT_ALIGNMENT);

    return result;
}

b32
rnMemoryArenaReleaseSlice(RnMemoryArena* self, RnMemorySlice value)
{
    ssize diff = value.values - self->values;
    ssize size = rnMemorySliceBytes(value);

    if (size <= 0 || diff < 0 || diff + size > self->size)
        return 0;

    if (diff % RN_MEMORY_DEFAULT_ALIGNMENT != 0) return 0;

    self->count = diff;

    return 1;
}

#endif // RN_BASE_MEMORY_ARENA_C
