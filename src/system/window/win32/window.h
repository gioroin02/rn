#ifndef P_SYSTEM_WIN32_WINDOW_WINDOW_H
#define P_SYSTEM_WIN32_WINDOW_WINDOW_H

#include "event.h"

typedef struct PWin32Window
{
    HWND  handle;
    HDC   device;
    HGLRC opengl;

    PWindowAttribs attribs;

    void* timer_ctxt;
    void* timer_proc;
}
PWin32Window;

PWin32Window* pWin32WindowReserve(PMemoryArena* arena);

Bool pWin32WindowCreate(PWin32Window* self, PString8 title, Int width, Int height);

void pWin32WindowDestroy(PWin32Window* self);

Bool pWin32WindowPollEvent(PWin32Window* self, PWindowEvent* event);

void pWin32WindowSwapBuffers(PWin32Window* self);

Bool pWin32WindowSetAttribs(PWin32Window* self, PWindowAttribs attribs);

PWindowAttribs pWin32WindowGetAttribs(PWin32Window* self);

Bool pWin32WindowSetTimerCallback(PWin32Window* self, void* ctxt, void* proc);

void* pWin32WindowGetTimerCallback(PWin32Window* self);

#endif
