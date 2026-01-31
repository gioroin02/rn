#ifndef RHO_SYSTEM_WINDOW_WIN32_WINDOW_H
#define RHO_SYSTEM_WINDOW_WIN32_WINDOW_H

#include "event.h"

typedef struct RWin32Window
{
    HWND  handle;
    HDC   device;
    HGLRC opengl;

    RWindowAttribs attribs;

    void* trig_ctxt;
    void* trig_proc;
}
RWin32Window;

RWin32Window* rho_win32_window_reserve(RMemoryArena* arena);

RBool32 rho_win32_window_create(RWin32Window* self, RString8 title, RInt width, RInt height);

void rho_win32_window_destroy(RWin32Window* self);

RBool32 rho_win32_window_poll_event(RWin32Window* self, RWindowEvent* event);

void rho_win32_window_swap_buffers(RWin32Window* self);

RBool32 rho_win32_window_set_attribs(RWin32Window* self, RWindowAttribs attribs);

RWindowAttribs rho_win32_window_get_attribs(RWin32Window* self);

RBool32 rho_win32_window_set_callback(RWin32Window* self, void* ctxt, void* proc);

void* rho_win32_window_get_callback(RWin32Window* self);

#endif
