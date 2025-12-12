#ifndef RN_STRUCTURE_MAP_C
#define RN_STRUCTURE_MAP_C

#include "./map.h"

static ssize
__rnMapHash__(RnMapTag* self, void* key)
{
    return ((rnProcHash*) self->procHash)(key);
}

static b32
__rnMapIsEqual__(RnMapTag* self, void* key, void* other)
{
    return ((rnProcIsEqual*) self->procIsEqual)(key, other);
}

static ssize
__rnMapDistance__(RnMapTag* self, void* key, ssize index)
{
    ssize size  = self->size;
    ssize probe = __rnMapHash__(self, key) % size;

    if (index < probe)
        return size + index - probe;

    return index - probe;
}

static ssize
__rnMapIndexForKey__(RnMapTag* self, void* keys, void* key)
{
    if (key == 0 || self->count == 0) return -1;

    ssize size  = self->size;
    ssize probe = __rnMapHash__(self, key) % size;

    for (ssize dist = 0; dist < size; dist += 1) {
        ssize index = self->indices[probe];

        if (index < 0) break;

        void* otherKey = &((u8*) keys)[index * self->kstep];

        if (__rnMapIsEqual__(self, key, otherKey) != 0) return probe;

        if (dist > __rnMapDistance__(self, otherKey, index))
            break;

        probe = (probe + 1) % size;
    }

    return -1;
}

b32
__rnMapCreate__(RnMapTag* self, void** kpntr, ssize kstep, void** vpntr, ssize vstep,
    RnMemoryArena* arena, ssize size, void* hash, void* isEqual)
{
    if (kstep <= 0 || vstep <= 0 || size <= 0) return 0;

    ssize* indices = rnMemoryArenaReserveManyOf(arena, ssize, size);
    u8*    keys    = rnMemoryArenaReserve(arena, size, kstep, 0);
    u8*    values  = rnMemoryArenaReserve(arena, size, vstep, 0);

    if (indices != 0 && keys != 0 && values != 0) {
        *self = (RnMapTag) {0};

        self->size        = size;
        self->indices     = indices;
        self->kstep       = kstep;
        self->vstep       = vstep;
        self->procHash    = hash;
        self->procIsEqual = isEqual;

        *kpntr = keys;
        *vpntr = values;

        __rnMapClear__(self);

        return 1;
    }

    rnMemoryArenaRelease(arena, indices);

    return 0;
}

ssize
__rnMapSize__(RnMapTag* self)
{
    return self->size;
}

ssize
__rnMapCount__(RnMapTag* self)
{
    return self->count;
}

b32
__rnMapIsEmpty__(RnMapTag* self)
{
    return self->count == 0 ? 1 : 0;
}

b32
__rnMapIsFull__(RnMapTag* self)
{
    return self->count == self->size ? 1 : 0;
}

b32
__rnMapIsKey__(RnMapTag* self, void* keys, void* key)
{
    ssize index = __rnMapIndexForKey__(self, keys, key);

    if (index < 0) return 0;

    self->index = self->indices[index];

    return 1;
}

void
__rnMapClear__(RnMapTag* self)
{
    self->count = 0;

    for (ssize i = 0; i < self->size; i += 1)
        self->indices[i] = -1;
}

b32
__rnMapSlotOpen__(RnMapTag* self, void* keys, void* key)
{
    if (key == 0 || self->count == self->size) return 0;

    ssize size  = self->size;
    ssize probe = __rnMapHash__(self, key) % size;

    for (ssize dist = 0; dist < size; dist += 1) {
        ssize index = self->indices[probe];

        if (index < 0) {
            self->index          = probe;
            self->indices[probe] = -1;

            return 1;
        }

        void* otherKey = &((u8*) keys)[index * self->kstep];

        if (__rnMapIsEqual__(self, key, otherKey) != 0) break;

        ssize otherDist = __rnMapDistance__(self, otherKey, index);

        if (dist > otherDist) {
            self->indices[probe] = index;
            dist                 = otherDist;
        }

        probe = (probe + 1) % size;
    }

    return 0;
}

#endif // RN_STRUCTURE_MAP_C
