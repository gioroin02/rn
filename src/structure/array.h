#ifndef RN_STRUCTURE_ARRAY_H
#define RN_STRUCTURE_ARRAY_H

#include "./import.h"

#define RN_ARRAY_TAG struct { ssize size; ssize count; }

#define rnArrayInsert(self, index, value) \
    (rnArrayGrow(self, (self)->values, index, rnManyStep((self)->values)) ? \
        ((self)->values[(index)] = value, ++(self)->count) : 0)

b32
rnArrayGrow(void* meta, void* values, ssize index, ssize step);

#endif // RN_STRUCTURE_ARRAY_H
