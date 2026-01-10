#ifndef PX_SYSTEM_WINDOW_WINDOW_H
#define PX_SYSTEM_WINDOW_WINDOW_H

#include "event.h"
#include "surface.h"

typedef enum PxWindowVisibility
{
    PxWindowVisibility_None,
    PxWindowVisibility_Hide,
    PxWindowVisibility_Show,
}
PxWindowVisibility;

typedef void PxWindow;

typedef void (PxWindowProcPaint) (void*);

PxWindow* pxWindowReserve(PxMemoryArena* arena);

b32 pxWindowCreate(PxWindow* self, PxString8 title, ssize width, ssize height);

void pxWindowDestroy(PxWindow* self);

ssize pxWindowWidth(PxWindow* self);

ssize pxWindowHeight(PxWindow* self);

void pxWindowClear(PxWindow* self, u8 red, u8 green, u8 blue);

void pxWindowPaint(PxWindow* self, ssize x, ssize y, ssize width, ssize height, PxWindowSurface* surface);

void pxWindowFlush(PxWindow* self);

b32 pxWindowPollEvent(PxWindow* self, PxWindowEvent* event);

b32 pxWindowVisibilitySet(PxWindow* self, PxWindowVisibility visibility);

void pxWindowProcPaintSet(PxWindow* self, void* ctxt, void* proc);

#endif // PX_SYSTEM_WINDOW_WINDOW_H
