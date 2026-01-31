#ifndef RHO_SYSTEM_WINDOW_OPENGL_WINDOW_C
#define RHO_SYSTEM_WINDOW_OPENGL_WINDOW_C

#include "window.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RWindow__ RWin32Window

    #define __rho_window_opengl_create__  rho_win32_window_opengl_create
    #define __rho_window_opengl_destroy__ rho_win32_window_opengl_destroy
    #define __rho_window_opengl_enable__  rho_win32_window_opengl_enable

#else

    #error "Unknown platform"

#endif

RBool32 rho_window_opengl_create(RWindow* self, ROpenglContextAttribs attribs)
{
    return __rho_window_opengl_create__((__RWindow__*) self, attribs);
}

void rho_window_opengl_destroy(RWindow* self)
{
    return __rho_window_opengl_destroy__((__RWindow__*) self);
}

RBool32 rho_window_opengl_enable(RWindow* self, RBool32 state)
{
    return __rho_window_opengl_enable__((__RWindow__*) self, state);
}

#endif
