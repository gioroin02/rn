#ifndef RN_STRUCTURE_ARRAY_C
#define RN_STRUCTURE_ARRAY_C

#include "./array.h"

typedef struct RnMetaArray
{
    ssize size;
    ssize count;
}
RnMetaArray;

ssize
rnMetaArraySize(void* meta)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (self != 0)
        return self->size;

    return 0;
}

ssize
rnMetaArrayCount(void* meta)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (self != 0)
        return self->count;

    return 0;
}

ssize
rnMetaArrayFront(void* meta)
{
    return 0;
}

ssize
rnMetaArrayBack(void* meta)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (self != 0 && self->count > 0)
        return self->count - 1;

    return 0;
}

b32
rnMetaArrayIsEmpty(void* meta)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (self != 0 && self->count == 0)
        return 1;

    return 0;
}

b32
rnMetaArrayIsFull(void* meta)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (self != 0 && self->count == self->size)
        return 1;

    return 0;
}

b32
rnMetaArrayIsIndex(void* meta, ssize index)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (self == 0 || index < 0 || index >= self->count)
        return 0;

    return 1;
}

b32
rnMetaArrayExtend(void* meta, void* values, ssize index, ssize step)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (self == 0 || values == 0 || step <= 0 || index < 0 || index > self->count)
        return 0;

    ssize start = step * self->count;
    ssize stop  = step * index;

    for (ssize i = start; i > stop; i -= 1)
        ((u8*) values)[i + step - 1] = ((u8*) values)[i - 1];

    self->count += 1;

    return 1;
}

b32
rnMetaArrayShrink(void* meta, void* values, ssize index, void* value, ssize step)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (self == 0 || values == 0 || step <= 0 || index < 0 || index >= self->count)
        return 0;

    self->count -= 1;

    ssize start = step * index;
    ssize stop  = step * self->count;

    if (value != 0) {
        for (ssize i = 0; i < step; i += 1)
            ((u8*) value)[i] = ((u8*) values)[i + index];
    }

    for (ssize i = start; i < stop; i += 1)
        ((u8*) values)[i] = ((u8*) values)[i + step];

    return 1;
}

#endif // RN_STRUCTURE_ARRAY_C
