#ifndef PX_STRUCTURE_MAP_C
#define PX_STRUCTURE_MAP_C

#include "map.h"

static ssize
__pxMapHash__(PxMapTag* self, void* key)
{
    return ((pxProcHash*) self->procHash)(key);
}

static b32
__pxMapIsEqual__(PxMapTag* self, void* key, void* other)
{
    return ((pxProcIsEqual*) self->procIsEqual)(key, other);
}

static ssize
__pxMapDistance__(PxMapTag* self, void* key, ssize index)
{
    ssize size  = self->size;
    ssize probe = __pxMapHash__(self, key) % size;

    if (index < probe)
        return size + index - probe;

    return index - probe;
}

static ssize
__pxMapIndexForKey__(PxMapTag* self, void* keys, void* key)
{
    if (key == 0 || self->count == 0) return -1;

    ssize size  = self->size;
    ssize probe = __pxMapHash__(self, key) % size;

    for (ssize dist = 0; dist < size; dist += 1) {
        ssize index = self->indices[probe];

        if (index < 0) break;

        void* otherKey = &((u8*) keys)[index * self->kstep];

        if (__pxMapIsEqual__(self, key, otherKey) != 0) return probe;

        if (dist > __pxMapDistance__(self, otherKey, index))
            break;

        probe = (probe + 1) % size;
    }

    return -1;
}

b32
__pxMapCreate__(PxMapTag* self, void** kpntr, ssize kstep, void** vpntr, ssize vstep,
    PxMemoryArena* arena, ssize size, void* hash, void* isEqual)
{
    if (kstep <= 0 || vstep <= 0 || size <= 0) return 0;

    ssize* indices = pxMemoryArenaReserveManyOf(arena, ssize, size);
    u8*    keys    = pxMemoryArenaReserve(arena, size, kstep, 0);
    u8*    values  = pxMemoryArenaReserve(arena, size, vstep, 0);

    if (indices != 0 && keys != 0 && values != 0) {
        *self = (PxMapTag) {0};

        self->size        = size;
        self->indices     = indices;
        self->kstep       = kstep;
        self->vstep       = vstep;
        self->procHash    = hash;
        self->procIsEqual = isEqual;

        *kpntr = keys;
        *vpntr = values;

        __pxMapClear__(self);

        return 1;
    }

    pxMemoryArenaRelease(arena, indices);

    return 0;
}

ssize
__pxMapSize__(PxMapTag* self)
{
    return self->size;
}

ssize
__pxMapCount__(PxMapTag* self)
{
    return self->count;
}

b32
__pxMapIsEmpty__(PxMapTag* self)
{
    return self->count == 0 ? 1 : 0;
}

b32
__pxMapIsFull__(PxMapTag* self)
{
    return self->count == self->size ? 1 : 0;
}

b32
__pxMapIsKey__(PxMapTag* self, void* keys, void* key)
{
    ssize index = __pxMapIndexForKey__(self, keys, key);

    if (index < 0) return 0;

    self->index = self->indices[index];

    return 1;
}

void
__pxMapClear__(PxMapTag* self)
{
    self->count = 0;

    for (ssize i = 0; i < self->size; i += 1)
        self->indices[i] = -1;
}

b32
__pxMapSlotOpen__(PxMapTag* self, void* keys, void* key)
{
    if (key == 0 || self->count == self->size) return 0;

    ssize size  = self->size;
    ssize probe = __pxMapHash__(self, key) % size;

    for (ssize dist = 0; dist < size; dist += 1) {
        ssize index = self->indices[probe];

        if (index < 0) {
            self->index          = probe;
            self->indices[probe] = -1;

            return 1;
        }

        void* otherKey = &((u8*) keys)[index * self->kstep];

        if (__pxMapIsEqual__(self, key, otherKey) != 0) break;

        ssize otherDist = __pxMapDistance__(self, otherKey, index);

        if (dist > otherDist) {
            self->indices[probe] = index;
            dist                 = otherDist;
        }

        probe = (probe + 1) % size;
    }

    return 0;
}

#endif // PX_STRUCTURE_MAP_C
