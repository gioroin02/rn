#ifndef P_SYSTEM_WINDOW_WINDOW_H
#define P_SYSTEM_WINDOW_WINDOW_H

#include "event.h"
#include "bitmap.h"

typedef enum PWindowVisibility
{
    PWindowVisibility_None,
    PWindowVisibility_Hide,
    PWindowVisibility_Show,
}
PWindowVisibility;

typedef void PWindow;

typedef void (PWindowProcUpdate) (PWindow*);

PWindow* pWindowReserve(PMemoryArena* arena);

b32 pWindowCreate(PWindow* self, PString8 title, ssize width, ssize height);

void pWindowDestroy(PWindow* self);

void pWindowClear(PWindow* self, u8 red, u8 green, u8 blue);

void pWindowPaint(PWindow* self, ssize x, ssize y, ssize width, ssize height, PBitmap* bitmap);

void pWindowFlush(PWindow* self);

b32 pWindowPollEvent(PWindow* self, PWindowEvent* event);

ssize pWindowWidthSet(PWindow* self, ssize width);

ssize pWindowWidthGet(PWindow* self);

ssize pWindowHeightSet(PWindow* self, ssize height);

ssize pWindowHeightGet(PWindow* self);

void* pWindowPntrContextSet(PWindow* self, void* ctxt);

void* pWindowPntrContextGet(PWindow* self);

void* pWindowProcUpdateSet(PWindow* self, void* proc);

void* pWindowProcUpdateGet(PWindow* self);

b32 pWindowVisibilitySet(PWindow* self, PWindowVisibility visibility);

PWindowVisibility pWindowVisibilityGet(PWindow* self);

#endif // P_SYSTEM_WINDOW_WINDOW_H
