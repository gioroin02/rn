#ifndef P_SYSTEM_WIN32_WINDOW_COMMON_C
#define P_SYSTEM_WIN32_WINDOW_COMMON_C

#include "common.h"

extern Int pWin32WindowProcRegular(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam);

static volatile LONG p_win32_winclass_count = 0;

Bool pWin32WindowStart()
{
    if (InterlockedIncrement(&p_win32_winclass_count) == 1)
        return pWin32WindowStartImpl();

    return 1;
}

Bool pWin32WindowStartImpl()
{
    WNDCLASSEXW window_class;

    pMemorySet(&window_class, sizeof window_class, 0x00);

    window_class.cbSize        = sizeof window_class;
    window_class.style         = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc   = pWin32WindowProcRegular;
    window_class.hInstance     = GetModuleHandle(NULL);
    window_class.lpszClassName = L"PWindowRegular";
    window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);

    if (RegisterClassExW(&window_class) == 0) return 0;

    return 1;
}

void pWin32WindowStop()
{
    if (InterlockedDecrement(&p_win32_winclass_count) == 0)
        pWin32WindowStopImpl();
}

void pWin32WindowStopImpl()
{
    UnregisterClassW(L"PWindowRegular", GetModuleHandle(NULL));
}

PString16 pWin32Str8ToStr16(U16* pntr, Int size, PString8 string)
{
    PString16 result = pString16Make(NULL, 0);

     size = MultiByteToWideChar(CP_UTF8, 0,
        (char*) string.values, string.size, (LPWSTR) pntr, size);

     if (size > 0) result = pString16Make(pntr, size);

     return result;
}

#endif // P_SYSTEM_WIN32_WINDOW_COMMON_C
