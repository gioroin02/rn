#ifndef P_GRAPHICS_WIN32_OPENGL_COMMON_C
#define P_GRAPHICS_WIN32_OPENGL_COMMON_C

#include "common.h"

void* pWin32OpenglLoader(void* symbol)
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
