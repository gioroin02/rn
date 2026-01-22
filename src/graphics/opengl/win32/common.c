#ifndef P_GRAPHICS_WIN32_OPENGL_COMMON_C
#define P_GRAPHICS_WIN32_OPENGL_COMMON_C

#include "common.h"

void* pWin32OpenglLoader(void* symbol)
{
    void*   result = wglGetProcAddress((LPCSTR) symbol);
    HMODULE module = NULL;

    if (result != NULL) return result;

    module = LoadLibraryA("opengl32.dll");

    return GetProcAddress(module, (LPCSTR) symbol);
}

#endif // P_GRAPHICS_WIN32_OPENGL_COMMON_C
