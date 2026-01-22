#ifndef P_SYSTEM_WINDOW_WINDOW_H
#define P_SYSTEM_WINDOW_WINDOW_H

#include "event.h"

typedef enum PWindowVisibility
{
    PWindowVisibility_None,
    PWindowVisibility_Hide,
    PWindowVisibility_Show,
}
PWindowVisibility;

typedef struct PWindowAttribs
{
    PWindowVisibility visibility;

    Int coord_x;
    Int coord_y;

    Int width;
    Int width_max;
    Int width_min;

    Int height;
    Int height_max;
    Int height_min;
}
PWindowAttribs;

typedef struct PWindow { U8 __private__; } PWindow;

typedef void (PWindowCallback) (void*, PWindow*);

PWindow* pWindowReserve(PMemoryArena* arena);

Bool pWindowCreate(PWindow* self, PString8 title, Int width, Int height);

void pWindowDestroy(PWindow* self);

Bool pWindowPollEvent(PWindow* self, PWindowEvent* event);

void pWindowSwapBuffers(PWindow* self);

Bool pWindowSetAttribs(PWindow* self, PWindowAttribs attribs);

PWindowAttribs pWindowGetAttribs(PWindow* self);

Bool pWindowSetCallback(PWindow* self, void* ctxt, void* proc);

void* pWindowGetCallback(PWindow* self);

#endif // P_SYSTEM_WINDOW_WINDOW_H
