#ifndef P_STRUCTURE_MAP_C
#define P_STRUCTURE_MAP_C

#include "map.h"

static Int __pMapHash__(PMapTag* self, void* key)
{
    return ((PMapProcHash*) self->map_proc_hash)(key);
}

static B32 __pMapIsEqual__(PMapTag* self, void* key, void* other)
{
    return ((PMapProcIsEqual*) self->map_proc_is_equal)(key, other);
}

static Int __pMapDistance__(PMapTag* self, void* key, Int index)
{
    Int size  = self->map_size;
    Int probe = __pMapHash__(self, key) % size;

    if (index < probe)
        return size + index - probe;

    return index - probe;
}

static Int __pMapIndexForKey__(PMapTag* self, void* keys, void* key)
{
    Int size  = self->map_size;
    Int probe = __pMapHash__(self, key) % size;
    Int index = self->map_indices[probe];

    if (key == NULL || self->map_count == 0) return -1;

    for (Int dist = 0; dist < size && index >= 0; dist += 1) {
        void* other_key = &((U8*) keys)[index * self->map_stride_key];

        if (__pMapIsEqual__(self, key, other_key) != 0) return probe;

        if (dist > __pMapDistance__(self, other_key, index))
            break;

        probe = (probe + 1) % size;
        index = self->map_indices[probe];
    }

    return -1;
}

B32 __pMapCreate__(PMapTag* self, void** pntrk, Int stridek, void** pntrv, Int stridev,
    PMemoryArena* arena, Int size, void* proc_hash, void* proc_is_equal)
{
    pMemorySet(self, sizeof *self, 0xAB);

    self->map_size          = 0;
    self->map_count         = 0;
    self->map_stride_key    = 0;
    self->map_stride_value  = 0;
    self->map_indices       = NULL;
    self->map_proc_hash     = NULL;
    self->map_proc_is_equal = NULL;
    self->map_index         = 0;

    if (pntrk == NULL || pntrv == NULL || size < 0 || stridek <= 0 || stridev <= 0)
        return 0;

    *pntrk = NULL;
    *pntrv = NULL;

    if (size == 0) return 1;

    void* mark = pMemoryArenaTell(arena);

    Int* pntr_indices = pMemoryArenaReserveManyOf(arena, Int, size);
    U8*  pntr_keys    = pMemoryArenaReserve(arena, size, stridek);
    U8*  pntr_values  = pMemoryArenaReserve(arena, size, stridev);

    if (pntr_indices != NULL && pntr_keys != NULL && pntr_values != NULL) {
        self->map_size          = size;
        self->map_stride_key    = stridek;
        self->map_stride_value  = stridev;
        self->map_indices       = pntr_indices;
        self->map_proc_hash     = proc_hash;
        self->map_proc_is_equal = proc_is_equal;

        for (Int i = 0; i < self->map_size; i += 1)
            self->map_indices[i] = -1;

        *pntrk = pntr_keys;
        *pntrv = pntr_values;

        return 1;
    }

    pMemoryArenaRewind(arena, mark);

    return 0;
}

Int __pMapSize__(PMapTag* self)
{
    return self->map_size;
}

Int __pMapCount__(PMapTag* self)
{
    return self->map_count;
}

B32 __pMapIsEmpty__(PMapTag* self)
{
    return self->map_count == 0 ? 1 : 0;
}

B32 __pMapIsFull__(PMapTag* self)
{
    return self->map_count == self->map_size ? 1 : 0;
}

B32 __pMapIsKey__(PMapTag* self, void* keys, void* key)
{
    Int index = __pMapIndexForKey__(self, keys, key);

    if (index < 0) return 0;

    self->map_index = self->map_indices[index];

    return 1;
}

void __pMapClear__(PMapTag* self)
{
    for (Int i = 0; i < self->map_size; i += 1)
        self->map_indices[i] = -1;

    self->map_count = 0;
}

B32 __pMapSlotOpen__(PMapTag* self, void* keys, void* key)
{
    if (self->map_count == self->map_size) return 0;

    Int size  = self->map_size;
    Int probe = __pMapHash__(self, key) % size;
    Int index = self->map_indices[probe];

    for (Int dist = 0; dist < size && index >= 0; dist += 1) {
        void* other_key  = &((U8*) keys)[index * self->map_stride_key];
        Int   other_dist = 0;

        if (__pMapIsEqual__(self, key, other_key) != 0) break;

        other_dist = __pMapDistance__(self, other_key, index);

        if (dist > other_dist) {
            self->map_indices[probe] = index;
            dist                     = other_dist;
        }

        probe = (probe + 1) % size;
        index = self->map_indices[probe];
    }

    self->map_index          = probe;
    self->map_indices[probe] = -1;

    return 1;
}

#endif
