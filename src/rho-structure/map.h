#ifndef RHO_STRUCTURE_MAP_H
#define RHO_STRUCTURE_MAP_H

#include "import.h"

#define __RMapTag__(ktype) struct { \
    RInt  map_size;                 \
    RInt  map_count;                \
    RInt  map_stride_key;           \
    RInt  map_stride_value;         \
    RInt* map_indices;              \
    void* map_proc_hash;            \
    void* map_proc_is_equal;        \
    RInt  map_index;                \
    ktype map_key;                  \
}

typedef struct RMapTag
{
    RInt  map_size;
    RInt  map_count;
    RInt  map_stride_key;
    RInt  map_stride_value;
    RInt* map_indices;
    void* map_proc_hash;
    void* map_proc_is_equal;
    RInt  map_index;
}
RMapTag;

typedef RInt    (RMapProcHash)    (void*);
typedef RBool32 (RMapProcIsEqual) (void*, void*);

#define RMap(ktype, vtype) struct {                 \
    __RMapTag__(ktype); ktype* keys; vtype* values; \
}

#define rho_array_pntr_keys(self)   ((self)->keys)
#define rho_array_pntr_values(self) ((self)->values)

#define rho_map_size(self)     __rho_map_size__(((RMapTag*) self))
#define rho_map_count(self)    __rho_map_count__(((RMapTag*) self))
#define rho_map_is_empty(self) __rho_map_is_empty__(((RMapTag*) self))
#define rho_map_is_full(self)  __rho_map_is_full__(((RMapTag*) self))

#define rho_map_is_key(self, key) ( \
    (self)->map_key = (key),        \
    __rho_map_is_key__(             \
        ((RMapTag*) self),          \
        (self)->keys,               \
        &(self)->map_key)           \
)

#define rho_map_clear(self) __rho_map_clear__(((RMapTag*) self))

#define rho_map_create(self, arena, size, proc_hash, proc_is_equal) ( \
    __rho_map_create__(                                               \
        ((RMapTag*) self),                                            \
        ((void**) &(self)->keys),                                     \
        sizeof *(self)->keys,                                         \
        ((void**) &(self)->values),                                   \
        sizeof *(self)->values,                                       \
        arena, size, proc_hash, proc_is_equal)                        \
)

#define rho_map_destroy(self) (     \
    __rho_map_destroy__(            \
        ((RMapTag*) self),          \
        ((void**) &(self)->keys),   \
        ((void**) &(self)->values)) \
)

#define rho_map_insert(self, key, value) (                           \
    (self)->map_key = (key),                                         \
    __rho_map_slot_open__(                                           \
        ((RMapTag*) self),                                           \
        (self)->keys,                                                \
        &(self)->map_key) != 0 ?                                     \
    (                                                                \
        (self)->map_indices[(self)->map_index]  = (self)->map_count, \
        (self)->keys[(self)->map_count]         = (self)->map_key,   \
        (self)->values[(self)->map_count]       = (value),           \
        (self)->map_count                     += 1                   \
    ), 1 : 0                                                         \
)

#define rho_map_get(self, key, other) \
    (rho_map_is_key(self, key) != 0 ? (self)->values[(self)->map_index] : (other))

#define rho_map_get_pntr(self, key) \
    (rho_map_is_key(self, key) != 0 ? &(self)->values[(self)->map_index] : NULL)

RBool32 __rho_map_create__(RMapTag* self, void** pntrk, RInt stridek, void** pntrv, RInt stridev,
    RMemoryArena* arena, RInt size, void* proc_hash, void* proc_is_equal);

void __rho_map_destroy__(RMapTag* self, void** pntrk, void** pntrv);

RInt __rho_map_size__(RMapTag* self);

RInt __rho_map_count__(RMapTag* self);

RBool32 __rho_map_is_empty__(RMapTag* self);

RBool32 __rho_map_is_full__(RMapTag* self);

RBool32 __rho_map_is_key__(RMapTag* self, void* keys, void* key);

void __rho_map_clear__(RMapTag* self);

RBool32 __rho_map_slot_open__(RMapTag* self, void* keys, void* key);

#endif
