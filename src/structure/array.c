#ifndef PX_STRUCTURE_ARRAY_C
#define PX_STRUCTURE_ARRAY_C

#include "array.h"

b32
__pxArrayCreate__(PxArrayTag* self, void** pntr, ssize step, PxMemoryArena* arena, ssize size)
{
    if (step <= 0 || size <= 0) return 0;

    u8* values = pxMemoryArenaReserve(arena, size, step, 0);

    if (values != 0) {
        *self = (PxArrayTag) {0};

        self->size = size;
        self->step = step;

        *pntr = values;

        return 1;
    }

    return 0;
}

ssize
__pxArraySize__(PxArrayTag* self)
{
    return self->size;
}

ssize
__pxArrayCount__(PxArrayTag* self)
{
    return self->count;
}

b32
__pxArrayIsEmpty__(PxArrayTag* self)
{
    return self->count == 0 ? 1 : 0;
}

b32
__pxArrayIsFull__(PxArrayTag* self)
{
    return self->count == self->size ? 1 : 0;
}

b32
__pxArrayIsIndex__(PxArrayTag* self, ssize index)
{
    if (index < 0 || index >= self->count)
        return 0;

    return 1;
}

ssize
__pxArrayFront__(PxArrayTag* self)
{
    return 0;
}

ssize
__pxArrayBack__(PxArrayTag* self)
{
    return self->count > 0 ? self->count - 1 : 0;
}

void
__pxArrayClear__(PxArrayTag* self)
{
    self->count = 0;
}

b32
__pxArrayCopy__(PxArrayTag* self, void* values, ssize index, void* value)
{
    if (index < 0 || index >= self->count) return 0;

    if (value == 0) return 1;

    for (ssize i = 0; i < self->step; i += 1)
        ((u8*) value)[i] = ((u8*) values)[i + index * self->step];

    return 1;
}

b32
__pxArraySlotOpen__(PxArrayTag* self, void* values, ssize index)
{
    if (index < 0 || index > self->count) return 0;

    ssize start = self->step * self->count;
    ssize stop  = self->step * index;

    for (ssize i = start; i > stop; i -= 1)
        ((u8*) values)[i + self->step - 1] = ((u8*) values)[i - 1];

    for (ssize i = 0; i < self->step; i += 1)
        ((u8*) values)[i + index * self->step] = 0;

    return 1;
}

b32
__pxArraySlotClose__(PxArrayTag* self, void* values, ssize index)
{
    if (index < 0 || index >= self->count) return 0;

    ssize start = self->step * index;
    ssize stop  = self->step * self->count;

    for (ssize i = start; i < stop; i += 1)
        ((u8*) values)[i] = ((u8*) values)[i + self->step];

    for (ssize i = 0; i < self->step; i += 1)
        ((u8*) values)[i + self->count * self->step] = 0;

    return 1;
}

#endif // PX_STRUCTURE_ARRAY_C
