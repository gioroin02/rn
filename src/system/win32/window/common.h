#ifndef PX_WIN32_WINDOW_COMMON_H
#define PX_WIN32_WINDOW_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

b32 pxWin32WindowStart();

b32 pxWin32WindowStartImpl();

void pxWin32WindowStop();

void pxWin32WindowStopImpl();

#endif // PX_WIN32_WINDOW_COMMON_H
