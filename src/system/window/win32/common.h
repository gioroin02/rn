#ifndef P_SYSTEM_WIN32_WINDOW_COMMON_H
#define P_SYSTEM_WIN32_WINDOW_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

B32 pWin32WindowStart();

B32 pWin32WindowStartImpl();

void pWin32WindowStop();

void pWin32WindowStopImpl();

PString16 pWin32Str8ToStr16(U16* pntr, Int size, PString8 string);

#endif
