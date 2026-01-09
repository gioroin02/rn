#ifndef PX_WIN32_WINDOW_WINDOW_H
#define PX_WIN32_WINDOW_WINDOW_H

#include "common.h"

typedef struct PxWin32Window
{
    HWND  handle;
    ssize drag_mode;
    POINT drag_cursor;
    RECT  drag_window;
    u32   color;
}
PxWin32Window;

PxWin32Window* pxWin32WindowReserve(PxMemoryArena* arena);

b32 pxWin32WindowCreate(PxWin32Window* self, PxString8 title, ssize width, ssize height);

void pxWin32WindowDestroy(PxWin32Window* self);

b32 pxWin32WindowPollEvent(PxWin32Window* self, PxWindowEvent* event);

b32 pxWin32WindowColorSet(PxWin32Window* self, u32 color);

b32 pxWin32WindowVisibilitySet(PxWin32Window* self, PxWindowVisibility visibility);

#endif // PX_WIN32_WINDOW_WINDOW_H
