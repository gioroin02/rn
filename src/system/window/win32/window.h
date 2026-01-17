#ifndef P_SYSTEM_WIN32_WINDOW_WINDOW_H
#define P_SYSTEM_WIN32_WINDOW_WINDOW_H

#include "bitmap.h"

typedef struct PWin32Window
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
PWin32Window;

PWin32Window* pWin32WindowReserve(PMemoryArena* arena);

b32 pWin32WindowCreate(PWin32Window* self, PString8 title, ssize width, ssize height);

void pWin32WindowDestroy(PWin32Window* self);

void pWin32WindowClear(PWin32Window* self, u8 red, u8 green, u8 blue);

void pWin32WindowPaint(PWin32Window* self, ssize x, ssize y, ssize width, ssize height, PWin32Bitmap* bitmap);

void pWin32WindowFlush(PWin32Window* self);

b32 pWin32WindowPollEvent(PWin32Window* self, PWindowEvent* event);

ssize pWin32windowWidthSet(PWin32Window* self, ssize width);

ssize pWin32WindowWidthGet(PWin32Window* self);

ssize pWin32windowHeightSet(PWin32Window* self, ssize height);

ssize pWin32WindowHeightGet(PWin32Window* self);

void* pWin32WindowPntrContextSet(PWin32Window* self, void* ctxt);

void* pWin32WindowProcUpdateSet(PWin32Window* self, void* proc);

b32 pWin32WindowVisibilitySet(PWin32Window* self, PWindowVisibility visibility);

#endif // P_SYSTEM_WIN32_WINDOW_WINDOW_H
