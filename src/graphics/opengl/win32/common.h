#ifndef P_GRAPHICS_WIN32_OPENGL_COMMON_H
#define P_GRAPHICS_WIN32_OPENGL_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "gdi32.dll")

#include <windows.h>
#include <wingdi.h>

typedef HGLRC (WINAPI* WglCreateContextAttribsARB) (HDC, HGLRC, int*);
typedef BOOL  (WINAPI* WglChoosePixelFormatARB)    (HDC, int*, FLOAT*, UINT, int*, UINT*);

static WglCreateContextAttribsARB wglCreateContextAttribsARB;
static WglChoosePixelFormatARB    wglChoosePixelFormatARB;

void* pWin32OpenglLoader(void* symbol);

#endif
