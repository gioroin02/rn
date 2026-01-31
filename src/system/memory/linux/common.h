#ifndef RHO_SYSTEM_MEMORY_LINUX_COMMON_H
#define RHO_SYSTEM_MEMORY_LINUX_COMMON_H

#include "import.h"

#ifndef _DEFAULT_SOURCE

    #define _DEFAULT_SOURCE

#endif

#include <unistd.h>
#include <errno.h>

#include <sys/mman.h>

RInt rho_linux_memory_page_size();

RMemoryArena rho_linux_memory_reserve(RInt size);

RBool32 rho_linux_memory_release(RMemoryArena* arena);

#endif
