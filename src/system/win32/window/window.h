#ifndef PX_WIN32_WINDOW_WINDOW_H
#define PX_WIN32_WINDOW_WINDOW_H

#include "surface.h"

typedef struct PxWin32Window
{
    HWND    handle;
    HDC     back_context;
    HBITMAP back_surface;
    u32     back_color;
    ssize   width_max;
    ssize   width_min;
    ssize   height_max;
    ssize   height_min;
    void*   paint_ctxt;
    void*   paint_proc;
}
PxWin32Window;

PxWin32Window* pxWin32WindowReserve(PxMemoryArena* arena);

b32 pxWin32WindowCreate(PxWin32Window* self, PxString8 title, ssize width, ssize height);

void pxWin32WindowDestroy(PxWin32Window* self);

ssize pxWin32WindowWidth(PxWin32Window* self);

ssize pxWin32WindowHeight(PxWin32Window* self);

void pxWin32WindowClear(PxWin32Window* self, u8 red, u8 green, u8 blue);

void pxWin32WindowPaint(PxWin32Window* self, ssize x, ssize y,
    ssize width, ssize height, PxWin32WindowSurface* surface);

void pxWin32WindowFlush(PxWin32Window* self);

b32 pxWin32WindowPollEvent(PxWin32Window* self, PxWindowEvent* event);

b32 pxWin32WindowVisibilitySet(PxWin32Window* self, PxWindowVisibility visibility);

void pxWin32WindowProcPaintSet(PxWin32Window* self, void* ctxt, void* proc);

#endif // PX_WIN32_WINDOW_WINDOW_H
