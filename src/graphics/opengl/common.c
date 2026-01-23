#ifndef P_GRAPHICS_OPENGL_COMMON_C
#define P_GRAPHICS_OPENGL_COMMON_C

#include "common.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __pOpenglLoader__ pWin32OpenglLoader

#else

    #error "Unknown platform"

#endif

void* pOpenglLoader(void* symbol)
{
    return __pOpenglLoader__(symbol);
}

#endif
