#ifndef RHO_GRAPHICS_OPENGL_WIN32_COMMON_C
#define RHO_GRAPHICS_OPENGL_WIN32_COMMON_C

#include "common.h"

void* rWin32OpenglLoader(void* symbol)
{
    void*   result = wglGetProcAddress((LPCSTR) symbol);
    HMODULE module = NULL;

    if (result == NULL) {
        module = LoadLibraryA("opengl32.dll");
        result = GetProcAddress(module, (LPCSTR) symbol);
    }

    return result;
}

#endif
