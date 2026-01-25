#ifndef P_SYSTEM_WIN32_WINDOW_OPENGL_WINDOW_H
#define P_SYSTEM_WIN32_WINDOW_OPENGL_WINDOW_H

#include "common.h"

B32 pWin32WindowOpenglCreate(PWin32Window* self, POpenglContextAttribs attribs);

void pWin32WindowOpenglDestroy(PWin32Window* self);

B32 pWin32WindowOpenglEnable(PWin32Window* self, B32 state);

#endif
