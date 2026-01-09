#ifndef PX_WIN32_WINDOW_WINDOW_H
#define PX_WIN32_WINDOW_WINDOW_H

#include "surface.h"

typedef struct PxWin32Window
{
    HWND    handle;
    HDC     back_context;
    HBITMAP back_surface;
    u32     back_color;
    ssize   drag_mode;
    POINT   drag_cursor;
    RECT    drag_window;
}
PxWin32Window;

PxWin32Window* pxWin32WindowReserve(PxMemoryArena* arena);

b32 pxWin32WindowCreate(PxWin32Window* self, PxString8 title, ssize width, ssize height);

void pxWin32WindowDestroy(PxWin32Window* self);

void pxWin32WindowClear(PxWin32Window* self);

void pxWin32WindowFlush(PxWin32Window* self, PxWin32WindowSurface* surface);

b32 pxWin32WindowPollEvent(PxWin32Window* self, PxWindowEvent* event);

void pxWin32WindowClearColorSet(PxWin32Window* self, u8 red, u8 green, u8 blue, u8 alpha);

b32 pxWin32WindowVisibilitySet(PxWin32Window* self, PxWindowVisibility visibility);

#endif // PX_WIN32_WINDOW_WINDOW_H
