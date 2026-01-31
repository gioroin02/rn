#ifndef RHO_SYSTEM_WINDOW_WINDOW_C
#define RHO_SYSTEM_WINDOW_WINDOW_C

#include "window.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RWindow__ RWin32Window

    #define __rho_window_reserve__      rho_win32_window_reserve
    #define __rho_window_create__       rho_win32_window_create
    #define __rho_window_destroy__      rho_win32_window_destroy
    #define __rho_window_poll_event__   rho_win32_window_poll_event
    #define __rho_window_swap_buffers__ rho_win32_window_swap_buffers
    #define __rho_window_set_attribs__  rho_win32_window_set_attribs
    #define __rho_window_get_attribs__  rho_win32_window_get_attribs
    #define __rho_window_set_callback__ rho_win32_window_set_callback
    #define __rho_window_get_callback__ rho_win32_window_get_callback

#else

    #error "Unknown platform"

#endif

RWindowAttribs rho_window_attribs_make()
{
    RWindowAttribs result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.visibility = RWindowVisibility_None;
    result.coord_x    = 0;
    result.coord_y    = 0;
    result.width      = 0;
    result.width_max  = 0;
    result.width_min  = 0;
    result.height     = 0;
    result.height_max = 0;
    result.height_min = 0;

    return result;
}

RWindow* rho_window_reserve(RMemoryArena* arena)
{
    return (RWindow*) __rho_window_reserve__(arena);
}

RBool32 rho_window_create(RWindow* self, RString8 title, RInt width, RInt height)
{
    return __rho_window_create__((__RWindow__*) self, title, width, height);
}

void rho_window_destroy(RWindow* self)
{
    return __rho_window_destroy__((__RWindow__*) self);
}

RBool32 rho_window_poll_event(RWindow* self, RWindowEvent* event)
{
    return __rho_window_poll_event__((__RWindow__*) self, event);
}

void rho_window_swap_buffers(RWindow* self)
{
    return __rho_window_swap_buffers__((__RWindow__*) self);
}

RBool32 rho_window_set_attribs(RWindow* self, RWindowAttribs attribs)
{
    return __rho_window_set_attribs__((__RWindow__*) self, attribs);
}

RWindowAttribs rho_window_get_attribs(RWindow* self)
{
    return __rho_window_get_attribs__((__RWindow__*) self);
}

RBool32 rho_window_set_callback(RWindow* self, void* ctxt, void* proc)
{
    return __rho_window_set_callback__((__RWindow__*) self, ctxt, proc);
}

void* rho_window_get_callback(RWindow* self)
{
    return __rho_window_get_callback__((__RWindow__*) self);
}

#endif
