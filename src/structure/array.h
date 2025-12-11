#ifndef RN_STRUCTURE_ARRAY_H
#define RN_STRUCTURE_ARRAY_H

#include "./import.h"

#define __RnArrayTag__ struct \
{                             \
    ssize size;               \
    ssize count;              \
    ssize vstep;              \
}

typedef __RnArrayTag__ RnArrayTag;

#define RnArray(type) struct \
{                            \
    __RnArrayTag__;          \
                             \
    type* values;            \
}

#define rnArrayCreate(self, arena, size) ( \
    __rnArrayCreate__(                     \
        ((RnArrayTag*) self),              \
        ((void**) &(self)->values),        \
        sizeof(*(self)->values),           \
        arena, size                        \
    )                                      \
)

#define rnArraySize(self)           __rnArraySize__(((RnArrayTag*) self))
#define rnArrayCount(self)          __rnArrayCount__(((RnArrayTag*) self))
#define rnArrayFront(self)          __rnArrayFront__(((RnArrayTag*) self))
#define rnArrayBack(self)           __rnArrayBack__(((RnArrayTag*) self))
#define rnArrayIsEmpty(self)        __rnArrayIsEmpty__(((RnArrayTag*) self))
#define rnArrayIsFull(self)         __rnArrayIsFull__(((RnArrayTag*) self))
#define rnArrayIsIndex(self, index) __rnArrayIsIndex__(((RnArrayTag*) self), index)
#define rnArrayClear(self)          __rnArrayClear__(((RnArrayTag*) self))

#define rnArrayCopy(self, index, value)   \
(                                         \
    __rnArrayCopy__(((RnArrayTag*) self), \
        (self)->values, index, value)     \
)

#define rnArrayInsert(self, index, value)   \
(                                           \
    __rnArraySlotOpen__(                    \
        ((RnArrayTag*) self),               \
        (self)->values,                     \
        index                               \
    ) != 0 ? (                              \
        (self)->values[(index)]  = (value), \
        (self)->count         += 1          \
    ), 1                                    \
    :  0                                    \
)

#define rnArrayRemove(self, index, value)  \
(                                          \
    rnArrayCopy(self, index, value) != 0   \
    ? (                                    \
        __rnArraySlotClose__(              \
            ((RnArrayTag*) self),          \
            (self)->values,                \
            index                          \
        ),                                 \
        (self)->count -= 1                 \
    ), 1                                   \
    :  0                                   \
)

#define rnArrayPushFront(self, value) rnArrayInsert(self, 0,                  value)
#define rnArrayPushBack(self, value)  rnArrayInsert(self, rnArrayCount(self), value)

#define rnArrayPopFront(self, value) rnArrayRemove(self, 0,                 value)
#define rnArrayPopBack(self, value)  rnArrayRemove(self, rnArrayBack(self), value)

#define rnArrayGet(self, index, other) \
    (rnArrayIsIndex(self, index) != 0 ? (self)->values[(index)] : (other))

#define rnArrayGetPtr(self, index) \
    (rnArrayIsIndex(self, index) != 0 ? &(self)->values[(index)] : 0)

b32
__rnArrayCreate__(RnArrayTag* self, void** vptr, ssize vstep, RnMemoryArena* arena, ssize size);

ssize
__rnArraySize__(RnArrayTag* self);

ssize
__rnArrayCount__(RnArrayTag* self);

ssize
__rnArrayFront__(RnArrayTag* self);

ssize
__rnArrayBack__(RnArrayTag* self);

b32
__rnArrayIsEmpty__(RnArrayTag* self);

b32
__rnArrayIsFull__(RnArrayTag* self);

b32
__rnArrayIsIndex__(RnArrayTag* self, ssize index);

void
__rnArrayClear__(RnArrayTag* self);

b32
__rnArrayCopy__(RnArrayTag* self, void* values, ssize index, void* value);

b32
__rnArraySlotOpen__(RnArrayTag* self, void* values, ssize index);

b32
__rnArraySlotClose__(RnArrayTag* self, void* values, ssize index);

#endif // RN_STRUCTURE_ARRAY_H
