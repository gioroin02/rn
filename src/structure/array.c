#ifndef RN_STRUCTURE_ARRAY_C
#define RN_STRUCTURE_ARRAY_C

#include "./array.h"

void*
__rnArrayCreate__(RnArrayHeader* self, void* values, RnMemoryArena* arena, ssize size, ssize step)
{
    if (self == 0 || values != 0 || step <= 0 || size <= 0)
        return 0;

    self->count = 0;
    self->size  = 0;
    self->step  = step;

    u8* memory = rnMemoryArenaReserve(arena, size, step, 0);

    if (memory != 0) self->size = size;

    return memory;
}

ssize
__rnArraySize__(RnArrayHeader* self)
{
    return self != 0 ? self->size : 0;
}

ssize
__rnArrayCount__(RnArrayHeader* self)
{
    return self != 0 ? self->count : 0;
}

ssize
__rnArrayFront__(RnArrayHeader* self)
{
    return 0;
}

ssize
__rnArrayBack__(RnArrayHeader* self)
{
    if (self != 0 && self->count > 0)
        return self->count - 1;

    return 0;
}

b32
__rnArrayIsEmpty__(RnArrayHeader* self)
{
    if (self != 0 && self->count == 0)
        return 1;

    return 0;
}

b32
__rnArrayIsFull__(RnArrayHeader* self)
{
    if (self != 0 && self->count == self->size)
        return 1;

    return 0;
}

b32
__rnArrayIsIndex__(RnArrayHeader* self, ssize index)
{
    if (self == 0 || index < 0 || index >= self->count)
        return 0;

    return 1;
}

void
__rnArrayClear__(RnArrayHeader* self)
{
    if (self != 0) self->count = 0;
}

b32
__rnArrayCopy__(RnArrayHeader* self, void* values, ssize index, void* value)
{
    if (self == 0 || values == 0 || index < 0 || index >= self->count)
        return 0;

    if (value == 0) return 1;

    for (ssize i = 0; i < self->step; i += 1)
        ((u8*) value)[i] = ((u8*) values)[i + index * self->step];

    return 1;
}

b32
__rnArrayShiftRight__(RnArrayHeader* self, void* values, ssize index)
{
    if (self == 0 || values == 0 || index < 0 || index > self->count)
        return 0;

    ssize start = self->step * self->count;
    ssize stop  = self->step * index;

    for (ssize i = start; i > stop; i -= 1)
        ((u8*) values)[i + self->step - 1] = ((u8*) values)[i - 1];

    for (ssize i = 0; i < self->step; i += 1)
        ((u8*) values)[i + index * self->step] = 0;

    return 1;
}

b32
__rnArrayShiftLeft__(RnArrayHeader* self, void* values, ssize index)
{
    if (self == 0 || values == 0 || index < 0 || index >= self->count)
        return 0;

    ssize start = self->step * index;
    ssize stop  = self->step * self->count;

    for (ssize i = start; i < stop; i += 1)
        ((u8*) values)[i] = ((u8*) values)[i + self->step];

    for (ssize i = 0; i < self->step; i += 1)
        ((u8*) values)[i + self->count * self->step] = 0;

    return 1;
}

#endif // RN_STRUCTURE_ARRAY_C
