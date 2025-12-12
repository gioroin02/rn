#ifndef RN_STRUCTURE_MAP_H
#define RN_STRUCTURE_MAP_H

#include "./import.h"

#define __RnMapTag__(ktype) \
    struct {                \
        ssize  size;        \
        ssize  count;       \
        ssize  kstep;       \
        ssize  vstep;       \
        ssize* indices;     \
        void*  procHash;    \
        void*  procIsEqual; \
        ssize  index;       \
        ktype  key;         \
    }

typedef __RnMapTag__(void*) RnMapTag;

typedef ssize (rnProcHash)    (void*);
typedef b32   (rnProcIsEqual) (void*, void*);

#define RnMap(ktype, vtype)  \
    struct {                 \
        __RnMapTag__(ktype); \
                             \
        ktype* keys;         \
        vtype* values;       \
    }

#define rnMapSize(self)       __rnMapSize__(((RnMapTag*) self))
#define rnMapCount(self)      __rnMapCount__(((RnMapTag*) self))
#define rnMapIsEmpty(self)    __rnMapIsEmpty__(((RnMapTag*) self))
#define rnMapIsFull(self)     __rnMapIsFull__(((RnMapTag*) self))

#define rnMapIsKey(self, key) ( \
    (self)->key = (key),        \
    __rnMapIsKey__(             \
        ((RnMapTag*) self),     \
        (self)->keys,           \
        &(self)->key            \
    )                           \
)

#define rnMapClear(self) __rnMapClear__(((RnMapTag*) self))

#define rnMapCreate(self, arena, size, proc, isEqual) ( \
    __rnMapCreate__(                                    \
        ((RnMapTag*) self),                             \
        ((void**) &(self)->keys),                       \
        sizeof(*(self)->keys),                          \
        ((void**) &(self)->values),                     \
        sizeof(*(self)->values),                        \
        arena, size, proc, isEqual                      \
    )                                                   \
)

#define rnMapInsert(self, key, value) (                  \
    (self)->key = (key),                                 \
    __rnMapSlotOpen__(                                   \
        ((RnMapTag*) self),                              \
        (self)->keys,                                    \
        &(self)->key                                     \
    ) != 0 ? (                                           \
        (self)->indices[(self)->index]  = (self)->count, \
        (self)->keys[(self)->count]     = (key),         \
        (self)->values[(self)->count]   = (value),       \
        (self)->count                  += 1              \
    ), 1                                                 \
    :  0                                                 \
)

#define rnMapGet(self, key, other) \
    (rnMapIsKey(self, key) != 0 ? (self)->values[(self)->index] : (other))

#define rnMapGetPtr(self, key) \
    (rnMapIsKey(self, key) != 0 ? &(self)->values[(self)->index] : 0)

b32
__rnMapCreate__(RnMapTag* self, void** kpntr, ssize kstep, void** vpntr, ssize vstep,
    RnMemoryArena* arena, ssize size, void* proc, void* isEqual);

ssize
__rnMapSize__(RnMapTag* self);

ssize
__rnMapCount__(RnMapTag* self);

b32
__rnMapIsEmpty__(RnMapTag* self);

b32
__rnMapIsFull__(RnMapTag* self);

b32
__rnMapIsKey__(RnMapTag* self, void* keys, void* key);

void
__rnMapClear__(RnMapTag* self);

b32
__rnMapSlotOpen__(RnMapTag* self, void* keys, void* key);

#endif // RN_STRUCTURE_MAP_H
