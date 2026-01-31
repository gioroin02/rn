#ifndef RHO_SYSTEM_MEMORY_WIN32_COMMON_H
#define RHO_SYSTEM_MEMORY_WIN32_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN
#define NOGDI

#include <windows.h>

RInt rho_win32_memory_page_size();

RMemoryArena rho_win32_memory_reserve(RInt size);

RBool32 rho_win32_memory_release(RMemoryArena* arena);

#endif
