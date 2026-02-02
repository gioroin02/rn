#ifndef RHO_GRAPHICS_OPENGL_WIN32_COMMON_H
#define RHO_GRAPHICS_OPENGL_WIN32_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "gdi32.dll")

#include <windows.h>
#include <wingdi.h>

void* rWin32OpenglLoader(void* symbol);

#endif
