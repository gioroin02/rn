#ifndef RN_STRUCTURE_MAP_H
#define RN_STRUCTURE_MAP_H

#include "./import.h"

#define RnMapTag struct                  \
{                                        \
    ssize* indices;                      \
                                         \
    ssize size;                          \
    ssize count;                         \
    ssize kstep;                         \
    ssize vstep;                         \
                                         \
    ssize (*hashProc)    (void*);        \
    b32   (*isEqualProc) (void*, void*); \
}

#define RnMap(ktype, vtype) struct \
{                                  \
    RnMapTag map;                  \
                                   \
    ktype* keys;                   \
    vtype* values;                 \
}

typedef RnMapTag RnMapHeader;

#define rnMapSize(self)    __rnMapSize__(&(self)->map)
#define rnMapCount(self)   __rnMapCount__(&(self)->map)
#define rnMapIsEmpty(self) __rnMapIsEmpty(&(self)->map)
#define rnMapIsFull(self)  __rnMapIsFull(&(self)->map)

#define rnMapIndexForKey(self, key)    \
(                                      \
    __rnMapIndexForKey__(&(self)->map, \
        (self)->keys, key)             \
)

ssize
__rnMapSize__(RnMapHeader* self);

ssize
__rnMapCount__(RnMapHeader* self);

b32
__rnMapIsEmpty__(RnMapHeader* self);

b32
__rnMapIsFull__(RnMapHeader* self);

b32
__rnMapIndexForKey__(RnMapHeader* self, void* keys, void* key);

#endif // RN_STRUCTURE_MAP_H
