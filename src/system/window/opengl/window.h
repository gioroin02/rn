#ifndef P_SYSTEM_WINDOW_OPENGL_WINDOW_H
#define P_SYSTEM_WINDOW_OPENGL_WINDOW_H

#include "import.h"

B32 pWindowOpenglCreate(PWindow* self, POpenglContextAttribs attribs);

void pWindowOpenglDestroy(PWindow* self);

B32 pWindowOpenglEnable(PWindow* self, B32 state);

#endif
