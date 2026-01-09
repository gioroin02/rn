#ifndef PX_SYSTEM_WINDOW_WINDOW_H
#define PX_SYSTEM_WINDOW_WINDOW_H

#include "event.h"

typedef enum PxWindowVisibility
{
    PxWindowVisibility_None,
    PxWindowVisibility_Hide,
    PxWindowVisibility_Show,
}
PxWindowVisibility;

typedef void PxWindow;

PxWindow* pxWindowReserve(PxMemoryArena* arena);

b32 pxWindowCreate(PxWindow* self, PxString8 title, ssize width, ssize height);

void pxWindowDestroy(PxWindow* self);

b32 pxWindowPollEvent(PxWindow* self, PxWindowEvent* event);

b32 pxWindowColorSet(PxWindow* self, u32 color);

b32 pxWindowVisibilitySet(PxWindow* self, PxWindowVisibility visibility);

#endif // PX_SYSTEM_WINDOW_WINDOW_H
