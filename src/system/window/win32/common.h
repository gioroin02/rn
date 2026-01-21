#ifndef P_SYSTEM_WIN32_WINDOW_COMMON_H
#define P_SYSTEM_WIN32_WINDOW_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")

#include <windows.h>
#include <wingdi.h>

#include <GL/gl.h>

typedef HGLRC (WINAPI* LPFN_wglCreateContextAttribsARB) (HDC, HGLRC, const int*);
typedef BOOL  (WINAPI* LPFN_wglChoosePixelFormatARB)    (HDC, const int*, const FLOAT*, UINT, int*, UINT*);

static LPFN_wglCreateContextAttribsARB wglCreateContextAttribsARB = (LPFN_wglCreateContextAttribsARB) NULL;
static LPFN_wglChoosePixelFormatARB    wglChoosePixelFormatARB    = (LPFN_wglChoosePixelFormatARB) NULL;

Bool pWin32WindowStart();

Bool pWin32WindowStartImpl();

void pWin32WindowStop();

void pWin32WindowStopImpl();

POINT pWin32Point(Int x, Int y);

POINT pWin32CursorPoint(HWND handle);

RECT pWin32Rect(Int x, Int y, Int w, Int h);

RECT pWin32RectAdjusted(Int x, Int y, Int w, Int h);

RECT pWin32WindowRect(HWND handle);

RECT pWin32ClientRect(HWND handle);

PString16 pWin32Str8ToStr16(U16* pntr, Int size, PString8 string);

#endif // P_SYSTEM_WIN32_WINDOW_COMMON_H
