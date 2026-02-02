#ifndef RHO_GRAPHICS_OPENGL_COMMON_C
#define RHO_GRAPHICS_OPENGL_COMMON_C

#include "common.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __rho_opengl_loader__ rWin32OpenglLoader

#else

    #error "Unknown platform"

#endif

void* rho_opengl_loader(void* symbol)
{
    return __rho_opengl_loader__(symbol);
}

#endif
