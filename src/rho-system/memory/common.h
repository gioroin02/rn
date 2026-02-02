#ifndef RHO_SYSTEM_MEMORY_COMMON_H
#define RHO_SYSTEM_MEMORY_COMMON_H

#include "import.h"

RInt rho_system_memory_page_size();

RMemoryArena rho_system_memory_reserve(RInt size);

RBool32 rho_system_memory_release(RMemoryArena* arena);

#endif
