#ifndef P_SYSTEM_WINDOW_OPENGL_WINDOW_H
#define P_SYSTEM_WINDOW_OPENGL_WINDOW_H

#include "import.h"

Bool pWindowOpenglCreate(PWindow* self, POpenglContextAttribs attribs);

void pWindowOpenglDestroy(PWindow* self);

Bool pWindowOpenglEnable(PWindow* self, Bool state);

#endif // P_SYSTEM_WINDOW_OPENGL_WINDOW_H
