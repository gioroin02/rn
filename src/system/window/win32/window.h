#ifndef P_SYSTEM_WIN32_WINDOW_WINDOW_H
#define P_SYSTEM_WIN32_WINDOW_WINDOW_H

#include "frame_buffer.h"

typedef struct PWin32Window
{
    HWND handle;
    HDC  context;

    PWin32FrameBuffer buffer_front;
    PWin32FrameBuffer buffer_back;

    Int width_max;
    Int width_min;
    Int height_max;
    Int height_min;

    void* paint_ctxt;
    void* paint_proc;
}
PWin32Window;

PWin32Window* pWin32WindowReserve(PMemoryArena* arena);

Bool pWin32WindowCreate(PWin32Window* self, PString8 title, Int width, Int height);

void pWin32WindowDestroy(PWin32Window* self);

Bool pWin32WindowPollEvent(PWin32Window* self, PWindowEvent* event);

PWin32FrameBuffer* pWin32WindowGetBuffer(PWin32Window* self);

void pWin32WindowFlushBuffer(PWin32Window* self);

Bool pWin32WindowSetVisibility(PWin32Window* self, PWindowVisibility visibility);

PWindowVisibility pWin32WindowGetVisibility(PWin32Window* self);

Bool pWin32WindowSetCallback(PWin32Window* self, void* ctxt, void* proc);

void* pWin32WindowGetCallback(PWin32Window* self);

/*
Int pWin32windowWidthSet(PWin32Window* self, Int width);

Int pWin32WindowWidthGet(PWin32Window* self);

Int pWin32windowHeightSet(PWin32Window* self, Int height);

Int pWin32WindowHeightGet(PWin32Window* self);
*/

#endif // P_SYSTEM_WIN32_WINDOW_WINDOW_H
