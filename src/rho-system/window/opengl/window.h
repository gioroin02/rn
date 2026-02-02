#ifndef RHO_SYSTEM_WINDOW_OPENGL_WINDOW_H
#define RHO_SYSTEM_WINDOW_OPENGL_WINDOW_H

#include "import.h"

RBool32 rho_window_opengl_create(RWindow* self, ROpenglContextAttribs attribs);

void rho_window_opengl_destroy(RWindow* self);

RBool32 rho_window_opengl_enable(RWindow* self, RBool32 state);

#endif
