#ifndef PX_WIN32_WINDOW_WINDOW_H
#define PX_WIN32_WINDOW_WINDOW_H

#include "bitmap.h"

typedef struct PxWin32Window
{
    HWND    handle;
    HDC     front_context;
    HBITMAP front_buffer;
    HDC     back_context;
    HBITMAP back_buffer;
    u32     draw_color;
    void*   ctxt;
    void*   proc_update;
    ssize   width_max;
    ssize   width_min;
    ssize   height_max;
    ssize   height_min;
}
PxWin32Window;

PxWin32Window* pxWin32WindowReserve(PxMemoryArena* arena);

b32 pxWin32WindowCreate(PxWin32Window* self, PxString8 title, ssize width, ssize height, ssize scale);

void pxWin32WindowDestroy(PxWin32Window* self);

void pxWin32WindowClear(PxWin32Window* self, u8 red, u8 green, u8 blue);

void pxWin32WindowPaint(PxWin32Window* self, ssize x, ssize y, ssize width, ssize height, PxWin32Bitmap* bitmap);

void pxWin32WindowFlush(PxWin32Window* self);

b32 pxWin32WindowPollEvent(PxWin32Window* self, PxWindowEvent* event);

ssize pxWin32windowWidthSet(PxWin32Window* self, ssize width);

ssize pxWin32WindowWidthGet(PxWin32Window* self);

ssize pxWin32windowHeightSet(PxWin32Window* self, ssize height);

ssize pxWin32WindowHeightGet(PxWin32Window* self);

void* pxWin32WindowPntrContextSet(PxWin32Window* self, void* ctxt);

void* pxWin32WindowProcUpdateSet(PxWin32Window* self, void* proc);

b32 pxWin32WindowVisibilitySet(PxWin32Window* self, PxWindowVisibility visibility);

#endif // PX_WIN32_WINDOW_WINDOW_H
