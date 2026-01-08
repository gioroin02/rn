#ifndef PX_SYSTEM_WINDOW_WINDOW_H
#define PX_SYSTEM_WINDOW_WINDOW_H

#include "import.h"

typedef enum PxWindowVisibility
{
    PxWindowVisibility_None,
    PxWindowVisibility_Hide,
    PxWindowVisibility_Show,
}
PxWindowVisibility;

typedef void PxWindow;

PxWindow* pxWindowReserve(PxMemoryArena* arena);

b32 pxWindowCreate(PxWindow* self, PxStr8 title, ssize width, ssize height);

void pxWindowDestroy(PxWindow* self);

b32 pxWindowVisibilitySet(PxWindow* self, PxWindowVisibility visibility);

#endif // PX_SYSTEM_WINDOW_WINDOW_H
