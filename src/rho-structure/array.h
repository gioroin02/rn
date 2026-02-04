#ifndef RHO_STRUCTURE_ARRAY_H
#define RHO_STRUCTURE_ARRAY_H

#include "import.h"

#define __RArrayTag__() struct { \
    RInt array_size;             \
    RInt array_count;            \
    RInt array_stride;           \
    RInt array_index;            \
}

typedef struct
{
    RInt array_size;
    RInt array_count;
    RInt array_stride;
    RInt array_index;
}
RArrayTag;

#define RArray(type) struct { __RArrayTag__(); type* values; }

#define rho_array_pntr(self) ((self)->values)

#define rho_array_size(self)     __rho_array_size__(((RArrayTag*) self))
#define rho_array_count(self)    __rho_array_count__(((RArrayTag*) self))
#define rho_array_front(self)    __rho_array_front__(((RArrayTag*) self))
#define rho_array_back(self)     __rho_array_back__(((RArrayTag*) self))
#define rho_array_is_empty(self) __rho_array_is_empty__(((RArrayTag*) self))
#define rho_array_is_full(self)  __rho_array_is_full__(((RArrayTag*) self))

#define rho_array_is_index(self, index) ( \
    (self)->array_index = (index),        \
    __rho_array_is_index__(               \
        ((RArrayTag*) self),              \
        (self)->array_index)              \
)

#define rho_array_clear(self) __rho_array_clear__(((RArrayTag*) self))

#define rho_array_create(self, arena, size) ( \
    __rho_array_create__(                     \
        ((RArrayTag*) self),                  \
        ((void**) &(self)->values),           \
        sizeof *(self)->values,               \
        arena, size)                          \
)

#define rho_array_destroy(self) (   \
    __rho_array_destroy__(          \
        ((RArrayTag*) self),        \
        ((void**) &(self)->values)) \
)

#define rho_array_copy(self, index, value)  \
(                                           \
    __rho_array_copy__(((RArrayTag*) self), \
        (self)->values, index, value)       \
)

#define rho_array_insert(self, index, value)            \
(                                                       \
    (self)->array_index = (index),                      \
    __rho_array_slot_open__(                            \
        ((RArrayTag*) self),                            \
        (self)->values,                                 \
        (self)->array_index) != 0 ?                     \
    (                                                   \
        (self)->values[(self)->array_index]  = (value), \
        (self)->array_count                 += 1        \
    ), 1 : 0                                            \
)

#define rho_array_add(self, index)  \
(                                   \
    (self)->array_index = (index),  \
    __rho_array_slot_open__(        \
        ((RArrayTag*) self),        \
        (self)->values,             \
        (self)->array_index) != 0 ? \
    (                               \
        (self)->array_count += 1    \
    ), 1 : 0                        \
)

#define rho_array_remove(self, index, value)  \
(                                             \
    (self)->array_index = (index),            \
    rho_array_copy(self, index, value) != 0 ? \
    (                                         \
        __rho_array_slot_close__(             \
            ((RArrayTag*) self),              \
            (self)->values,                   \
            (self)->array_index),             \
        (self)->array_count -= 1              \
    ), 1 : 0                                  \
)

#define rho_array_drop(self, index) \
(                                   \
    (self)->array_index = (index),  \
    __rho_array_slot_close__(       \
        ((RArrayTag*) self),        \
        (self)->values,             \
        (self)->array_index) != 0 ? \
    (                               \
        (self)->array_count -= 1    \
    ), 1 : 0                        \
)

#define rho_array_insert_front(self, value) rho_array_insert(self, 0,                     value)
#define rho_array_insert_back(self, value)  rho_array_insert(self, rho_array_count(self), value)

#define rho_array_add_front(self) rho_array_add(self, 0)
#define rho_array_add_back(self)  rho_array_add(self, rho_array_count(self))

#define rho_array_remove_front(self, value) rho_array_remove(self, 0,                   value)
#define rho_array_remove_back(self, value)  rho_array_remove(self, rho_array_back(self), value)

#define rho_array_drop_front(self) rho_array_drop(self, 0)
#define rho_array_drop_back(self)  rho_array_drop(self, rho_array_back(self))

#define rho_array_get(self, index, other) \
    (rho_array_is_index(self, index) != 0 ? (self)->values[(self)->array_index] : (other))

#define rho_array_get_pntr(self, index) \
    (rho_array_is_index(self, index) != 0 ? &(self)->values[(self)->array_index] : NULL)

RBool32 __rho_array_create__(RArrayTag* self, void** pntr, RInt step, RMemoryArena* arena, RInt size);

void __rho_array_destroy__(RArrayTag* self, void** pntr);

RInt __rho_array_size__(RArrayTag* self);

RInt __rho_array_count__(RArrayTag* self);

RInt __rho_array_front__(RArrayTag* self);

RInt __rho_array_back__(RArrayTag* self);

RBool32 __rho_array_is_empty__(RArrayTag* self);

RBool32 __rho_array_is_full__(RArrayTag* self);

RBool32 __rho_array_is_index__(RArrayTag* self, RInt index);

void __rho_array_clear__(RArrayTag* self);

RBool32 __rho_array_copy__(RArrayTag* self, void* values, RInt index, void* value);

RBool32 __rho_array_slot_open__(RArrayTag* self, void* values, RInt index);

RBool32 __rho_array_slot_close__(RArrayTag* self, void* values, RInt index);

#endif
