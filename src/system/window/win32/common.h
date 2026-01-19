#ifndef P_SYSTEM_WIN32_WINDOW_COMMON_H
#define P_SYSTEM_WIN32_WINDOW_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "gdi32.lib")

#include <windows.h>

Bool pWin32WindowStart();

Bool pWin32WindowStartImpl();

void pWin32WindowStop();

void pWin32WindowStopImpl();

#endif // P_SYSTEM_WIN32_WINDOW_COMMON_H
