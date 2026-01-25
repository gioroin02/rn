#ifndef P_SYSTEM_WIN32_WINDOW_OPENGL_H
#define P_SYSTEM_WIN32_WINDOW_OPENGL_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "gdi32.lib")

#include <windows.h>
#include <wingdi.h>

typedef HGLRC (WINAPI* WglCreateContextAttribsARB) (HDC, HGLRC, int*);
typedef BOOL  (WINAPI* WglChoosePixelFormatARB)    (HDC, int*, FLOAT*, UINT, int*, UINT*);

WglCreateContextAttribsARB wglCreateContextAttribsARB;
WglChoosePixelFormatARB    wglChoosePixelFormatARB;

B32 pWin32WindowOpenglStart();

B32 pWin32WindowOpenglStartImpl();

void pWin32WindowOpenglStop();

void pWin32WindowOpenglStopImpl();

#endif
