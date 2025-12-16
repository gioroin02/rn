#ifndef PX_STRUCTURE_ARRAY_H
#define PX_STRUCTURE_ARRAY_H

#include "import.h"

#define __PxArrayTag__() \
    struct {             \
        ssize size;      \
        ssize count;     \
        ssize step;      \
    }

typedef __PxArrayTag__() PxArrayTag;

#define PxArray(type)     \
    struct {              \
        __PxArrayTag__(); \
                          \
        type* values;     \
    }

#define pxArrayCreate(self, arena, size) ( \
    __pxArrayCreate__(                     \
        ((PxArrayTag*) self),              \
        ((void**) &(self)->values),        \
        sizeof(*(self)->values),           \
        arena, size                        \
    )                                      \
)

#define pxArraySize(self)           __pxArraySize__(((PxArrayTag*) self))
#define pxArrayCount(self)          __pxArrayCount__(((PxArrayTag*) self))
#define pxArrayIsEmpty(self)        __pxArrayIsEmpty__(((PxArrayTag*) self))
#define pxArrayIsFull(self)         __pxArrayIsFull__(((PxArrayTag*) self))
#define pxArrayIsIndex(self, index) __pxArrayIsIndex__(((PxArrayTag*) self), index)
#define pxArrayFront(self)          __pxArrayFront__(((PxArrayTag*) self))
#define pxArrayBack(self)           __pxArrayBack__(((PxArrayTag*) self))
#define pxArrayClear(self)          __pxArrayClear__(((PxArrayTag*) self))

#define pxArrayCopy(self, index, value)   \
(                                         \
    __pxArrayCopy__(((PxArrayTag*) self), \
        (self)->values, index, value)     \
)

#define pxArrayInsert(self, index, value)   \
(                                           \
    __pxArraySlotOpen__(                    \
        ((PxArrayTag*) self),               \
        (self)->values,                     \
        index                               \
    ) != 0 ? (                              \
        (self)->values[(index)]  = (value), \
        (self)->count         += 1          \
    ), 1                                    \
    :  0                                    \
)

#define pxArrayRemove(self, index, value)  \
(                                          \
    pxArrayCopy(self, index, value) != 0   \
    ? (                                    \
        __pxArraySlotClose__(              \
            ((PxArrayTag*) self),          \
            (self)->values,                \
            index                          \
        ),                                 \
        (self)->count -= 1                 \
    ), 1                                   \
    :  0                                   \
)

#define pxArrayPushFront(self, value) pxArrayInsert(self, 0,                  value)
#define pxArrayPushBack(self, value)  pxArrayInsert(self, pxArrayCount(self), value)

#define pxArrayPopFront(self, value) pxArrayRemove(self, 0,                 value)
#define pxArrayPopBack(self, value)  pxArrayRemove(self, pxArrayBack(self), value)

#define pxArrayGet(self, index, other) \
    (pxArrayIsIndex(self, index) != 0 ? (self)->values[(index)] : (other))

#define pxArrayGetPtr(self, index) \
    (pxArrayIsIndex(self, index) != 0 ? &(self)->values[(index)] : 0)

b32
__pxArrayCreate__(PxArrayTag* self, void** pntr, ssize step, PxMemoryArena* arena, ssize size);

ssize
__pxArraySize__(PxArrayTag* self);

ssize
__pxArrayCount__(PxArrayTag* self);

b32
__pxArrayIsEmpty__(PxArrayTag* self);

b32
__pxArrayIsFull__(PxArrayTag* self);

b32
__pxArrayIsIndex__(PxArrayTag* self, ssize index);

ssize
__pxArrayFront__(PxArrayTag* self);

ssize
__pxArrayBack__(PxArrayTag* self);

void
__pxArrayClear__(PxArrayTag* self);

b32
__pxArrayCopy__(PxArrayTag* self, void* values, ssize index, void* value);

b32
__pxArraySlotOpen__(PxArrayTag* self, void* values, ssize index);

b32
__pxArraySlotClose__(PxArrayTag* self, void* values, ssize index);

#endif // PX_STRUCTURE_ARRAY_H
