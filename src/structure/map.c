#ifndef RHO_STRUCTURE_MAP_C
#define RHO_STRUCTURE_MAP_C

#include "map.h"

static RInt __rho_map_hash__(RMapTag* self, void* key)
{
    return ((RMapProcHash*) self->map_proc_hash)(key);
}

static RBool32 __rho_map_is_equal__(RMapTag* self, void* key, void* other)
{
    return ((RMapProcIsEqual*) self->map_proc_is_equal)(key, other);
}

static RInt __rho_map_distance__(RMapTag* self, void* key, RInt index)
{
    RInt size  = self->map_size;
    RInt probe = __rho_map_hash__(self, key) % size;

    if (index < probe)
        return size + index - probe;

    return index - probe;
}

static RInt __rho_map_index_for_key__(RMapTag* self, void* keys, void* key)
{
    RInt size  = self->map_size;
    RInt probe = __rho_map_hash__(self, key) % size;
    RInt index = self->map_indices[probe];

    if (key == NULL || self->map_count == 0) return -1;

    for (RInt dist = 0; dist < size && index >= 0; dist += 1) {
        void* other_key = &((RUint8*) keys)[index * self->map_stride_key];

        if (__rho_map_is_equal__(self, key, other_key) != 0) return probe;

        if (dist > __rho_map_distance__(self, other_key, index))
            break;

        probe = (probe + 1) % size;
        index = self->map_indices[probe];
    }

    return -1;
}

RBool32 __rho_map_create__(RMapTag* self, void** pntrk, RInt stridek, void** pntrv, RInt stridev,
    RMemoryArena* arena, RInt size, void* proc_hash, void* proc_is_equal)
{
    rho_memory_set(self, sizeof *self, 0xAB);

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

    void* mark = rho_memory_arena_tell(arena);

    RInt*   pntr_indices = rho_memory_arena_reserve_of(arena, RInt, size);
    RUint8* pntr_keys    = rho_memory_arena_reserve(arena, size, stridek);
    RUint8* pntr_values  = rho_memory_arena_reserve(arena, size, stridev);

    if (pntr_indices != NULL && pntr_keys != NULL && pntr_values != NULL) {
        self->map_size          = size;
        self->map_stride_key    = stridek;
        self->map_stride_value  = stridev;
        self->map_indices       = pntr_indices;
        self->map_proc_hash     = proc_hash;
        self->map_proc_is_equal = proc_is_equal;

        for (RInt i = 0; i < self->map_size; i += 1)
            self->map_indices[i] = -1;

        *pntrk = pntr_keys;
        *pntrv = pntr_values;

        return 1;
    }

    rho_memory_arena_rewind(arena, mark);

    return 0;
}

void __rho_map_destroy__(RMapTag* self, void** pntrk, void** pntrv)
{
    rho_memory_set(pntrk, sizeof *pntrk, 0xAB);
    rho_memory_set(pntrv, sizeof *pntrv, 0xAB);
    rho_memory_set(self,  sizeof *self,  0xAB);
}

RInt __rho_map_size__(RMapTag* self)
{
    return self->map_size;
}

RInt __rho_map_count__(RMapTag* self)
{
    return self->map_count;
}

RBool32 __rho_map_is_empty__(RMapTag* self)
{
    return self->map_count == 0 ? 1 : 0;
}

RBool32 __rho_map_is_full__(RMapTag* self)
{
    return self->map_count == self->map_size ? 1 : 0;
}

RBool32 __rho_map_is_key__(RMapTag* self, void* keys, void* key)
{
    RInt index = __rho_map_index_for_key__(self, keys, key);

    if (index < 0) return 0;

    self->map_index = self->map_indices[index];

    return 1;
}

void __rho_map_clear__(RMapTag* self)
{
    for (RInt i = 0; i < self->map_size; i += 1)
        self->map_indices[i] = -1;

    self->map_count = 0;
}

RBool32 __rho_map_slot_open__(RMapTag* self, void* keys, void* key)
{
    if (self->map_count == self->map_size) return 0;

    RInt size  = self->map_size;
    RInt probe = __rho_map_hash__(self, key) % size;
    RInt index = self->map_indices[probe];

    for (RInt dist = 0; dist < size && index >= 0; dist += 1) {
        void* other_key  = &((RUint8*) keys)[index * self->map_stride_key];
        RInt  other_dist = 0;

        if (__rho_map_is_equal__(self, key, other_key) != 0) break;

        other_dist = __rho_map_distance__(self, other_key, index);

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
