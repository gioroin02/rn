#ifndef RN_STRUCTURE_ARRAY_H
#define RN_STRUCTURE_ARRAY_H

#include "./import.h"

#define RnArrayTag struct \
{                         \
    ssize size;           \
    ssize count;          \
    ssize step;           \
}

typedef RnArrayTag RnArrayHeader;

#define RnArray(type) struct \
{                            \
    RnArrayHeader array;     \
                             \
    type* values;            \
}

#define rnArrayCreate(self, arena, size)                         \
(                                                                \
    (self)->values = __rnArrayCreate__(&(self)->array,           \
        (self)->values, arena, size, sizeof((self)->values[0])), \
    rnArraySize(self)                                            \
)

#define rnArraySize(self)           __rnArraySize__(&(self)->array)
#define rnArrayCount(self)          __rnArrayCount__(&(self)->array)
#define rnArrayFront(self)          __rnArrayFront__(&(self)->array)
#define rnArrayBack(self)           __rnArrayBack__(&(self)->array)
#define rnArrayIsEmpty(self)        __rnArrayIsEmpty__(&(self)->array)
#define rnArrayIsFull(self)         __rnArrayIsFull__(&(self)->array)
#define rnArrayIsIndex(self, index) __rnArrayIsIndex__(&(self)->array, index)
#define rnArrayClear(self)          __rnArrayClear__(&(self)->array)

#define rnArrayCopy(self, index, value) \
(                                       \
    __rnArrayCopy__(&(self)->array,     \
        (self)->values, index, value)   \
)

#define rnArrayShiftRight(self, index)    \
(                                         \
    __rnArrayShiftRight__(&(self)->array, \
        (self)->values, index)            \
)

#define rnArrayShiftLeft(self, index)    \
(                                        \
    __rnArrayShiftLeft__(&(self)->array, \
        (self)->values, index)           \
)

#define rnArrayInsert(self, index, value) \
(                                         \
    rnArrayShiftRight(self, index) != 0   \
    ? (                                   \
        (self)->values[index]  = value,   \
        (self)->array.count   += 1        \
    ), 1                                  \
    :  0                                  \
)

#define rnArrayRemove(self, index, value) \
(                                         \
    rnArrayCopy(self, index, value) != 0  \
    ? (                                   \
        rnArrayShiftLeft(self, index),    \
        (self)->array.count -= 1          \
    ), 1                                  \
    :  0                                  \
)

#define rnArrayPushFront(self, value) rnArrayInsert(self, 0,                  value)
#define rnArrayPushBack(self, value)  rnArrayInsert(self, rnArrayCount(self), value)

#define rnArrayPopFront(self, value) rnArrayRemove(self, 0,                 value)
#define rnArrayPopBack(self, value)  rnArrayRemove(self, rnArrayBack(self), value)

#define rnArrayGet(self, index, other) \
    (rnArrayIsIndex(self, index) != 0 ? (self)->values[index] : other)

#define rnArrayGetRef(self, index) \
    (rnArrayIsIndex(self, index) != 0 ? &(self)->values[index] : 0)

void*
__rnArrayCreate__(RnArrayHeader* self, void* values, RnMemoryArena* arena, ssize size, ssize step);

ssize
__rnArraySize__(RnArrayHeader* self);

ssize
__rnArrayCount__(RnArrayHeader* self);

ssize
__rnArrayFront__(RnArrayHeader* self);

ssize
__rnArrayBack__(RnArrayHeader* self);

b32
__rnArrayIsEmpty__(RnArrayHeader* self);

b32
__rnArrayIsFull__(RnArrayHeader* self);

b32
__rnArrayIsIndex__(RnArrayHeader* self, ssize index);

void
__rnArrayClear__(RnArrayHeader* self);

b32
__rnArrayCopy__(RnArrayHeader* self, void* values, ssize index, void* value);

b32
__rnArrayShiftRight__(RnArrayHeader* self, void* values, ssize index);

b32
__rnArrayShiftLeft__(RnArrayHeader* self, void* values, ssize index);

#endif // RN_STRUCTURE_ARRAY_H
