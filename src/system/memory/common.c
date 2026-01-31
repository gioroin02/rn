#ifndef RHO_SYSTEM_MEMORY_COMMON_C
#define RHO_SYSTEM_MEMORY_COMMON_C

#include "common.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __rho_system_memory_page_size__ rho_win32_memory_page_size
    #define __rho_system_memory_reserve__   rho_win32_memory_reserve
    #define __rho_system_memory_release__   rho_win32_memory_release

#elif RHO_SYSTEM == RHO_SYSTEM_LINUX

    #include "linux/export.c"

    #define __rho_system_memory_page_size__ rho_linux_memory_page_size
    #define __rho_system_memory_reserve__   rho_linux_memory_reserve
    #define __rho_system_memory_release__   rho_linux_memory_release

#else

    #error "Unknown platform"

#endif

RInt rho_system_memory_page_size()
{
    return __rho_system_memory_page_size__();
}

RMemoryArena rho_system_memory_reserve(RInt size)
{
    return __rho_system_memory_reserve__(size);
}

RBool32 rho_system_memory_release(RMemoryArena* arena)
{
    return __rho_system_memory_release__(arena);
}

#endif
