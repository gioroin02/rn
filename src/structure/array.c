#ifndef RN_STRUCTURE_ARRAY_C
#define RN_STRUCTURE_ARRAY_C

#include "./array.h"

typedef struct RnMetaArray
{
    ssize size;
    ssize count;
}
RnMetaArray;

b32
rnArrayGrow(void* meta, void* values, ssize index, ssize step)
{
    RnMetaArray* self = ((RnMetaArray*) meta);

    if (index < 0 || index > self->count)
        return 0;

    ssize start = step * self->count;
    ssize stop  = step * index;

    for (ssize i = start; i > stop; i -= 1)
        ((u8*) values)[i + step - 1] = ((u8*) values)[i - 1];

    return 1;
}

#endif // RN_STRUCTURE_ARRAY_C
