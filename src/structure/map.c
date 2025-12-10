#ifndef RN_STRUCTURE_MAP_C
#define RN_STRUCTURE_MAP_C

#include "./map.h"

static ssize
__rnMapKeyDistance__(RnMapHeader* self, void* key, ssize index)
{
    ssize size  = self->size;
    ssize probe = self->hashProc(key) % size;

    if (index < probe)
        return size + index - probe;

    return index - probe;
}

ssize
__rnMapSize__(RnMapHeader* self)
{
    return self != 0 ? self->size : 0;
}

ssize
__rnMapCount__(RnMapHeader* self)
{
    return self != 0 ? self->count : 0;
}

b32
__rnMapIsEmpty__(RnMapHeader* self)
{
    if (self != 0 && self->count == 0)
        return 1;

    return 0;
}

ssize
__rnMapIsFull__(RnMapHeader* self)
{
    if (self != 0 && self->count == self->size)
        return 1;

    return 0;
}

ssize
__rnMapIndexForKey__(RnMapHeader* self, void* keys, void* key)
{
    if (self == 0 || keys == 0 || key == 0 || self->count == 0)
        return 0;

    ssize size  = self->size;
    ssize probe = self->hashProc(key) % size;

    for (ssize dist = 0; dist < size; dist += 1) {
        ssize index = self->indices[probe];

        if (index < 0) break;

        void* otherKey = &((u8*) keys)[index * self->kstep];

        if (self->isEqualProc(key, otherKey) != 0) return probe;

        if (dist > __rnMapDistance__(self, otherKey, index))
            break;

        probe = (probe + 1) % size;
    }

    return -1;
}

#endif // RN_STRUCTURE_MAP_C
