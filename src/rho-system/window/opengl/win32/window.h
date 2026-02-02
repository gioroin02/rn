#ifndef RHO_SYSTEM_WINDOW_OPENGL_WIN32_WINDOW_H
#define RHO_SYSTEM_WINDOW_OPENGL_WIN32_WINDOW_H

#include "common.h"

RBool32 rho_win32_window_opengl_create(RWin32Window* self, ROpenglContextAttribs attribs);

void rho_win32_window_opengl_destroy(RWin32Window* self);

RBool32 rho_win32_window_opengl_enable(RWin32Window* self, RBool32 state);

#endif
