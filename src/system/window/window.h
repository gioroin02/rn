#ifndef P_SYSTEM_WINDOW_WINDOW_H
#define P_SYSTEM_WINDOW_WINDOW_H

#include "event.h"
#include "frame_buffer.h"

typedef enum PWindowVisibility
{
    PWindowVisibility_None,
    PWindowVisibility_Hide,
    PWindowVisibility_Show,
}
PWindowVisibility;

typedef struct PWindow { U8 __private__; } PWindow;

typedef void (PWindowCallback) (void*, PWindow*, PFrameBuffer*);

PWindow* pWindowReserve(PMemoryArena* arena);

Bool pWindowCreate(PWindow* self, PString8 title, Int width, Int height);

void pWindowDestroy(PWindow* self);

Bool pWindowPollEvent(PWindow* self, PWindowEvent* event);

PFrameBuffer* pWindowGetBuffer(PWindow* self);

void pWindowFlushBuffer(PWindow* self);

Bool pWindowSetVisibility(PWindow* self, PWindowVisibility visibility);

PWindowVisibility pWindowGetVisibility(PWindow* self);

Bool pWindowSetCallback(PWindow* self, void* ctxt, void* proc);

void* pWindowGetCallback(PWindow* self);

/*
Int pWindowWidthSet(PWindow* self, Int width);

Int pWindowWidthGet(PWindow* self);

Int pWindowHeightSet(PWindow* self, Int height);

Int pWindowHeightGet(PWindow* self);
*/

#endif // P_SYSTEM_WINDOW_WINDOW_H
