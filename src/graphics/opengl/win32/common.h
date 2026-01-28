#ifndef P_GRAPHICS_WIN32_OPENGL_COMMON_H
#define P_GRAPHICS_WIN32_OPENGL_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "gdi32.dll")

#include <windows.h>
#include <wingdi.h>

void* pWin32OpenglLoader(void* symbol);

#endif
