#ifndef PX_STRUCTURE_MAP_H
#define PX_STRUCTURE_MAP_H

#include "import.h"

#define __PxMapTag__(ktype) \
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

typedef __PxMapTag__(void*) PxMapTag;

typedef ssize (pxProcHash)    (void*);
typedef b32   (pxProcIsEqual) (void*, void*);

#define PxMap(ktype, vtype)  \
    struct {                 \
        __PxMapTag__(ktype); \
                             \
        ktype* keys;         \
        vtype* values;       \
    }

#define pxMapSize(self)       __pxMapSize__(((PxMapTag*) self))
#define pxMapCount(self)      __pxMapCount__(((PxMapTag*) self))
#define pxMapIsEmpty(self)    __pxMapIsEmpty__(((PxMapTag*) self))
#define pxMapIsFull(self)     __pxMapIsFull__(((PxMapTag*) self))

#define pxMapIsKey(self, key) ( \
    (self)->key = (key),        \
    __pxMapIsKey__(             \
        ((PxMapTag*) self),     \
        (self)->keys,           \
        &(self)->key            \
    )                           \
)

#define pxMapClear(self) __pxMapClear__(((PxMapTag*) self))

#define pxMapCreate(self, arena, size, proc, isEqual) ( \
    __pxMapCreate__(                                    \
        ((PxMapTag*) self),                             \
        ((void**) &(self)->keys),                       \
        sizeof(*(self)->keys),                          \
        ((void**) &(self)->values),                     \
        sizeof(*(self)->values),                        \
        arena, size, proc, isEqual                      \
    )                                                   \
)

#define pxMapInsert(self, key, value) (                  \
    (self)->key = (key),                                 \
    __pxMapSlotOpen__(                                   \
        ((PxMapTag*) self),                              \
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

#define pxMapGet(self, key, other) \
    (pxMapIsKey(self, key) != 0 ? (self)->values[(self)->index] : (other))

#define pxMapGetPtr(self, key) \
    (pxMapIsKey(self, key) != 0 ? &(self)->values[(self)->index] : 0)

b32
__pxMapCreate__(PxMapTag* self, void** kpntr, ssize kstep, void** vpntr, ssize vstep,
    PxMemoryArena* arena, ssize size, void* proc, void* isEqual);

ssize
__pxMapSize__(PxMapTag* self);

ssize
__pxMapCount__(PxMapTag* self);

b32
__pxMapIsEmpty__(PxMapTag* self);

b32
__pxMapIsFull__(PxMapTag* self);

b32
__pxMapIsKey__(PxMapTag* self, void* keys, void* key);

void
__pxMapClear__(PxMapTag* self);

b32
__pxMapSlotOpen__(PxMapTag* self, void* keys, void* key);

#endif // PX_STRUCTURE_MAP_H
