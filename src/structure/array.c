#ifndef RN_STRUCTURE_ARRAY_C
#define RN_STRUCTURE_ARRAY_C

#include "./array.h"

b32
__rnArrayCreate__(RnArrayTag* self, void** vptr, ssize vstep, RnMemoryArena* arena, ssize size)
{
    if (vstep <= 0 || size <= 0) return 0;

    u8* values = rnMemoryArenaReserve(arena, size, vstep, 0);

    if (values != 0) {
        *self = (RnArrayTag) {0};

        self->size  = size;
        self->vstep = vstep;

        *vptr = values;

        return 1;
    }

    return 0;
}

ssize
__rnArraySize__(RnArrayTag* self)
{
    return self->size;
}

ssize
__rnArrayCount__(RnArrayTag* self)
{
    return self->count;
}

ssize
__rnArrayFront__(RnArrayTag* self)
{
    return 0;
}

ssize
__rnArrayBack__(RnArrayTag* self)
{
    return self->count > 0 ? self->count - 1 : 0;
}

b32
__rnArrayIsEmpty__(RnArrayTag* self)
{
    return self->count == 0 ? 1 : 0;
}

b32
__rnArrayIsFull__(RnArrayTag* self)
{
    return self->count == self->size ? 1 : 0;
}

b32
__rnArrayIsIndex__(RnArrayTag* self, ssize index)
{
    if (index < 0 || index >= self->count)
        return 0;

    return 1;
}

void
__rnArrayClear__(RnArrayTag* self)
{
    self->count = 0;
}

b32
__rnArrayCopy__(RnArrayTag* self, void* values, ssize index, void* value)
{
    if (index < 0 || index >= self->count) return 0;

    if (value == 0) return 1;

    for (ssize i = 0; i < self->vstep; i += 1)
        ((u8*) value)[i] = ((u8*) values)[i + index * self->vstep];

    return 1;
}

b32
__rnArraySlotOpen__(RnArrayTag* self, void* values, ssize index)
{
    if (index < 0 || index > self->count) return 0;

    ssize start = self->vstep * self->count;
    ssize stop  = self->vstep * index;

    for (ssize i = start; i > stop; i -= 1)
        ((u8*) values)[i + self->vstep - 1] = ((u8*) values)[i - 1];

    for (ssize i = 0; i < self->vstep; i += 1)
        ((u8*) values)[i + index * self->vstep] = 0;

    return 1;
}

b32
__rnArraySlotClose__(RnArrayTag* self, void* values, ssize index)
{
    if (index < 0 || index >= self->count) return 0;

    ssize start = self->vstep * index;
    ssize stop  = self->vstep * self->count;

    for (ssize i = start; i < stop; i += 1)
        ((u8*) values)[i] = ((u8*) values)[i + self->vstep];

    for (ssize i = 0; i < self->vstep; i += 1)
        ((u8*) values)[i + self->count * self->vstep] = 0;

    return 1;
}

#endif // RN_STRUCTURE_ARRAY_C
