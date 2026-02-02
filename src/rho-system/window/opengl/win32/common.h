#ifndef RHO_SYSTEM_WINDOW_OPENGL_WIN32_H
#define RHO_SYSTEM_WINDOW_OPENGL_WIN32_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "gdi32.lib")

#include <windows.h>
#include <wingdi.h>

typedef HGLRC (WINAPI* WglCreateContextAttribsARB) (HDC, HGLRC, int*);
typedef BOOL  (WINAPI* WglChoosePixelFormatARB)    (HDC, int*, FLOAT*, UINT, int*, UINT*);

extern WglCreateContextAttribsARB wglCreateContextAttribsARB;
extern WglChoosePixelFormatARB    wglChoosePixelFormatARB;

RBool32 rho_win32_window_opengl_start();

void rho_win32_window_opengl_stop();

#endif
