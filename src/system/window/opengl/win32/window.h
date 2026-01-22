#ifndef P_SYSTEM_WIN32_WINDOW_OPENGL_WINDOW_H
#define P_SYSTEM_WIN32_WINDOW_OPENGL_WINDOW_H

#include "common.h"

Bool pWin32WindowOpenglCreate(PWin32Window* self, POpenglContextAttribs attribs);

void pWin32WindowOpenglDestroy(PWin32Window* self);

Bool pWin32WindowOpenglEnable(PWin32Window* self, Bool state);

#endif // P_SYSTEM_WIN32_WINDOW_OPENGL_WINDOW_H
