#ifndef RHO_SYSTEM_WINDOW_WINDOW_H
#define RHO_SYSTEM_WINDOW_WINDOW_H

#include "event.h"

typedef enum RWindowVisibility
{
    RWindowVisibility_None,
    RWindowVisibility_Hide,
    RWindowVisibility_Show,
}
RWindowVisibility;

typedef enum RWindowTrigger
{
    RWindowTrigger_None,
    RWindowTrigger_Paint,
}
RWindowTrigger;

typedef struct RWindowAttribs
{
    RWindowVisibility visibility;

    RInt coord_x;
    RInt coord_y;

    RInt width;
    RInt width_max;
    RInt width_min;

    RInt height;
    RInt height_max;
    RInt height_min;
}
RWindowAttribs;

typedef struct RWindow { RUint8 __private__; } RWindow;

typedef void (RWindowCallback) (void*, RWindowTrigger);

RWindowAttribs rho_window_attribs_make();

RWindow* rho_window_reserve(RMemoryArena* arena);

RBool32 rho_window_create(RWindow* self, RString8 title, RInt width, RInt height);

void rho_window_destroy(RWindow* self);

RBool32 rho_window_poll_event(RWindow* self, RWindowEvent* event);

void rho_window_swap_buffers(RWindow* self);

RBool32 rho_window_set_attribs(RWindow* self, RWindowAttribs attribs);

RWindowAttribs rho_window_get_attribs(RWindow* self);

RBool32 rho_window_set_callback(RWindow* self, void* ctxt, void* proc);

void* rho_window_get_callback(RWindow* self);

#endif
