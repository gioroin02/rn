#ifndef RN_BASE_MEMORY_ARENA_C
#define RN_BASE_MEMORY_ARENA_C

#include "./arena.h"

RnMemoryArena
rn_memory_arena_from_slice(void* memory, ssize size)
{
    RnMemoryArena result = {0};

    if (memory == 0 || size <= 0)
        return result;

    result.values = rn_cast(u8*, memory);
    result.size   = size;

    return result;
}

void
rn_memory_arena_clear(RnMemoryArena* self)
{
    self->count = 0;
}

void*
rn_memory_arena_tell(RnMemoryArena* self)
{
    return self->values + self->count;
}

RnMemorySlice
rn_memory_arena_reserve_slice(RnMemoryArena* self, ssize amount, ssize step)
{
    RnMemorySlice result = {0};

    if (amount <= 0 || step <= 0 || amount > RN_MAX_SSIZE / step)
        return result;

    ssize size   = amount * step;
    void* memory = rn_memory_arena_tell(self);

    if (self->count < 0 || self->count + size > self->size)
        return result;

    result = rn_memory_slice_make(memory, 0, amount, step);

    rn_memory_slice_zero(result);

    self->count = rn_memory_align_forward(
        self->count + size, RN_MEMORY_DEFAULT_ALIGNMENT);

    return result;
}

b32
rn_memory_arena_release_slice(RnMemoryArena* self, RnMemorySlice value)
{
    ssize diff = value.values - self->values;
    ssize size = rn_memory_slice_bytes(value);

    if (size <= 0 || diff < 0 || diff + size > self->size)
        return 0;

    if (diff % RN_MEMORY_DEFAULT_ALIGNMENT != 0) return 0;

    self->count = diff;

    return 1;
}

#endif // RN_BASE_MEMORY_ARENA_C
