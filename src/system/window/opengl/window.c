#ifndef P_SYSTEM_WINDOW_OPENGL_WINDOW_C
#define P_SYSTEM_WINDOW_OPENGL_WINDOW_C

#include "window.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PWindow__ PWin32Window

    #define __pWindowOpenglCreate__  pWin32WindowOpenglCreate
    #define __pWindowOpenglDestroy__ pWin32WindowOpenglDestroy
    #define __pWindowOpenglEnable__  pWin32WindowOpenglEnable

#else

    #error "Unknown platform"

#endif

B32 pWindowOpenglCreate(PWindow* self, POpenglContextAttribs attribs)
{
    return __pWindowOpenglCreate__((__PWindow__*) self, attribs);
}

void pWindowOpenglDestroy(PWindow* self)
{
    return __pWindowOpenglDestroy__((__PWindow__*) self);
}

B32 pWindowOpenglEnable(PWindow* self, B32 state)
{
    return __pWindowOpenglEnable__((__PWindow__*) self, state);
}

#endif
