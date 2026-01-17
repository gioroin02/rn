#ifndef P_SYSTEM_WIN32_WINDOW_WINDOW_C
#define P_SYSTEM_WIN32_WINDOW_WINDOW_C

#include "window.h"

#define P_SYSTEM_WIN32_TIMER_RESIZE ((ssize) 1)

static POINT pWin32Point(ssize x, ssize y)
{
    POINT result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.x = x;
    result.y = y;

    return result;
}

static POINT pWin32CursorPoint(HWND handle)
{
    POINT result;

    pMemorySet(&result, sizeof result, 0xAB);

    GetCursorPos(&result);

    return result;
}

static RECT pWin32Rect(ssize x, ssize y, ssize w, ssize h)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.left   = x;
    result.top    = y;
    result.right  = x + w;
    result.bottom = y + h;

    return result;
}

static RECT pWin32RectAdjusted(ssize x, ssize y, ssize w, ssize h)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.left   = x;
    result.top    = y;
    result.right  = x + w;
    result.bottom = y + h;

    AdjustWindowRect(&result, 0, 0);

    return result;
}

static RECT pWin32WindowRect(HWND handle)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    GetWindowRect(handle, &result);

    return result;
}

static RECT pWin32ClientRect(HWND handle)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    GetClientRect(handle, &result);

    return result;
}

static PString16 pWin32Str8ToStr16(u16* pntr, ssize size, PString8 string)
{
    PString16 result = pString16Make(NULL, 0);

     size = MultiByteToWideChar(CP_UTF8, 0,
        (char*) string.values, string.size, (LPWSTR) pntr, size);

     if (size > 0) result = pString16Make(pntr, size);

     return result;
}

static PWindowKeyboardKey pWin32WindowConvertKey(WORD key_code)
{
    switch (key_code) {
        case 'A':            return PWindowKeyboardKey_A;            break;
        case 'B':            return PWindowKeyboardKey_B;            break;
        case 'C':            return PWindowKeyboardKey_C;            break;
        case 'D':            return PWindowKeyboardKey_D;            break;
        case 'E':            return PWindowKeyboardKey_E;            break;
        case 'F':            return PWindowKeyboardKey_F;            break;
        case 'G':            return PWindowKeyboardKey_G;            break;
        case 'H':            return PWindowKeyboardKey_H;            break;
        case 'I':            return PWindowKeyboardKey_I;            break;
        case 'J':            return PWindowKeyboardKey_J;            break;
        case 'K':            return PWindowKeyboardKey_K;            break;
        case 'L':            return PWindowKeyboardKey_L;            break;
        case 'M':            return PWindowKeyboardKey_M;            break;
        case 'N':            return PWindowKeyboardKey_N;            break;
        case 'O':            return PWindowKeyboardKey_O;            break;
        case 'P':            return PWindowKeyboardKey_P;            break;
        case 'Q':            return PWindowKeyboardKey_Q;            break;
        case 'R':            return PWindowKeyboardKey_R;            break;
        case 'S':            return PWindowKeyboardKey_S;            break;
        case 'T':            return PWindowKeyboardKey_T;            break;
        case 'U':            return PWindowKeyboardKey_U;            break;
        case 'V':            return PWindowKeyboardKey_V;            break;
        case 'W':            return PWindowKeyboardKey_W;            break;
        case 'X':            return PWindowKeyboardKey_X;            break;
        case 'Y':            return PWindowKeyboardKey_Y;            break;
        case 'Z':            return PWindowKeyboardKey_Z;            break;
        case '0':            return PWindowKeyboardKey_0;            break;
        case '1':            return PWindowKeyboardKey_1;            break;
        case '2':            return PWindowKeyboardKey_2;            break;
        case '3':            return PWindowKeyboardKey_3;            break;
        case '4':            return PWindowKeyboardKey_4;            break;
        case '5':            return PWindowKeyboardKey_5;            break;
        case '6':            return PWindowKeyboardKey_6;            break;
        case '7':            return PWindowKeyboardKey_7;            break;
        case '8':            return PWindowKeyboardKey_8;            break;
        case '9':            return PWindowKeyboardKey_9;            break;
        case VK_SPACE:       return PWindowKeyboardKey_Space;        break;
        case VK_OEM_MINUS:   return PWindowKeyboardKey_Minus;        break;
        case VK_OEM_PLUS:    return PWindowKeyboardKey_Equal;        break;
        case VK_OEM_4:       return PWindowKeyboardKey_SquareLeft;   break;
        case VK_OEM_6:       return PWindowKeyboardKey_SquareRight;  break;
        case VK_OEM_5:       return PWindowKeyboardKey_BackSlash;    break;
        case VK_OEM_1:       return PWindowKeyboardKey_SemiColon;    break;
        case VK_OEM_7:       return PWindowKeyboardKey_Apostrophe;   break;
        case VK_OEM_3:       return PWindowKeyboardKey_Grave;        break;
        case VK_OEM_COMMA:   return PWindowKeyboardKey_Comma;        break;
        case VK_OEM_PERIOD:  return PWindowKeyboardKey_Period;       break;
        case VK_OEM_2:       return PWindowKeyboardKey_Slash;        break;
        case VK_UP:          return PWindowKeyboardKey_Up;           break;
        case VK_DOWN:        return PWindowKeyboardKey_Down;         break;
        case VK_LEFT:        return PWindowKeyboardKey_Left;         break;
        case VK_RIGHT:       return PWindowKeyboardKey_Right;        break;
        case VK_HOME:        return PWindowKeyboardKey_Home;         break;
        case VK_END:         return PWindowKeyboardKey_End;          break;
        case VK_PRIOR:       return PWindowKeyboardKey_PageUp;       break;
        case VK_NEXT:        return PWindowKeyboardKey_PageDown;     break;
        case VK_INSERT:      return PWindowKeyboardKey_Insert;       break;
        case VK_DELETE:      return PWindowKeyboardKey_Delete;       break;
        case VK_F1:          return PWindowKeyboardKey_F1;           break;
        case VK_F2:          return PWindowKeyboardKey_F2;           break;
        case VK_F3:          return PWindowKeyboardKey_F3;           break;
        case VK_F4:          return PWindowKeyboardKey_F4;           break;
        case VK_F5:          return PWindowKeyboardKey_F5;           break;
        case VK_F6:          return PWindowKeyboardKey_F6;           break;
        case VK_F7:          return PWindowKeyboardKey_F7;           break;
        case VK_F8:          return PWindowKeyboardKey_F8;           break;
        case VK_F9:          return PWindowKeyboardKey_F9;           break;
        case VK_F10:         return PWindowKeyboardKey_F10;          break;
        case VK_F11:         return PWindowKeyboardKey_F11;          break;
        case VK_F12:         return PWindowKeyboardKey_F12;          break;
        case VK_RETURN:      return PWindowKeyboardKey_Enter;        break;
        case VK_ESCAPE:      return PWindowKeyboardKey_Escape;       break;
        case VK_BACK:        return PWindowKeyboardKey_BackSpace;    break;
        case VK_TAB:         return PWindowKeyboardKey_Tab;          break;

        default: break;
    }

    return PWindowKeyboardKey_None;
}

ssize pWin32WindowProc(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    PWin32Window* self = (PWin32Window*) GetWindowLongPtr(handle, GWLP_USERDATA);

    if (self == NULL) return DefWindowProcW(handle, kind, wparam, lparam);

    ssize result = 0;

    switch (kind) {
        case WM_ENTERSIZEMOVE:
            SetTimer(handle, P_SYSTEM_WIN32_TIMER_RESIZE, 10, NULL);
        break;

        case WM_EXITSIZEMOVE: KillTimer(handle, P_SYSTEM_WIN32_TIMER_RESIZE); break;

        case WM_TIMER: {
            if (wparam == P_SYSTEM_WIN32_TIMER_RESIZE) {
                if (self->proc_update != NULL)
                    ((PWindowProcUpdate*) self->proc_update)(self->ctxt);
            }
        } break;

        case WM_GETMINMAXINFO: {
            MINMAXINFO* info = (MINMAXINFO*) lparam;

            info->ptMinTrackSize.x = self->width_min;
            info->ptMaxTrackSize.x = self->width_max;
            info->ptMinTrackSize.y = self->height_min;
            info->ptMaxTrackSize.y = self->height_max;
        } break;

        case WM_ERASEBKGND: result = 1; break;

        case WM_PAINT: {
            PAINTSTRUCT paint;

            HDC context = BeginPaint(handle, &paint);

            ssize left   = paint.rcPaint.left;
            ssize top    = paint.rcPaint.top;
            ssize width  = paint.rcPaint.right - left;
            ssize height = paint.rcPaint.bottom - top;

            StretchBlt(context, left, top, width, height,
                self->front_context, 0, 0, width, height, SRCCOPY);

            EndPaint(handle, &paint);
        } break;

        case WM_CLOSE: PostQuitMessage(0); break;

        default: result = -1;
    }

    if (result < 0) return DefWindowProcW(handle, kind, wparam, lparam);

    return result;
}

PWin32Window* pWin32WindowReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32Window);
}

b32
pWin32WindowCreate(PWin32Window* self, PString8 title, ssize width, ssize height)
{
    static u16 buffer[P_MEMORY_KIB];

    if (width <= 0 || height <= 0 || width > P_SSIZE_MAX / height) return 0;

    RECT       rect   = pWin32RectAdjusted(0, 0, width, height);
    PString16 string = pWin32Str8ToStr16(buffer, sizeof buffer, title);

    if (string.size <= 0 || pWin32WindowStart() == 0) return 0;

    width  = rect.right - rect.left;
    height = rect.bottom - rect.top;

    HWND handle = CreateWindowW(L"PWindowRegular",
        string.values, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        width, height, NULL, NULL, NULL, NULL);

    if (handle != NULL) {
        self->handle        = handle;
        self->front_context = NULL;
        self->front_buffer  = NULL;
        self->back_context  = NULL;
        self->back_buffer   = NULL;
        self->draw_color    = 0;
        self->ctxt          = NULL;
        self->proc_update   = NULL;
        self->width_max     = 1920;
        self->width_min     = 320;
        self->height_max    = 1080;
        self->height_min    = 180;

        SetWindowLongPtr(self->handle, GWLP_USERDATA, (LONG_PTR) self);

        RECT rect    = pWin32ClientRect(self->handle);
        HDC  context = GetDC(self->handle);

        self->front_context = CreateCompatibleDC(context);
        self->back_context  = CreateCompatibleDC(context);

        self->front_buffer = CreateCompatibleBitmap(context,
            self->width_max, self->height_max);

        self->back_buffer = CreateCompatibleBitmap(context,
            self->width_max, self->height_max);

        ReleaseDC(self->handle, context);

        SelectObject(self->front_context, self->front_buffer);
        SetDCBrushColor(self->front_context, RGB(0, 0, 0));

        FillRect(self->front_context, &rect, GetStockObject(DC_BRUSH));

        InvalidateRect(self->handle, NULL, 0);

        return 1;
    }

    pWin32WindowStop();

    return 0;
}

void pWin32WindowDestroy(PWin32Window* self)
{
    if (self->handle != NULL) {
        if (GetCapture() == self->handle)
            ReleaseCapture();

        DeleteObject(self->back_buffer);
        DeleteObject(self->front_buffer);

        DeleteDC(self->back_context);
        DeleteDC(self->front_context);

        DestroyWindow(self->handle);
    }

    pMemorySet(self, sizeof *self, 0xAB);

    pWin32WindowStop();
}

void pWin32WindowClear(PWin32Window* self, u8 red, u8 green, u8 blue)
{
    RECT rect = pWin32ClientRect(self->handle);

    u32 color = ((u32) red)   << 0
              | ((u32) green) << 8
              | ((u32) blue)  << 16;

    self->draw_color = color;

    SetDCBrushColor(self->back_context, RGB(red, green, blue));
    FillRect(self->back_context, &rect, GetStockObject(DC_BRUSH));

    InvalidateRect(self->handle, NULL, 0);
}

void pWin32WindowPaint(PWin32Window* self, ssize x, ssize y, ssize width, ssize height, PWin32Bitmap* bitmap)
{
    if (self->back_buffer == NULL || bitmap == NULL) return;

    RECT rect = pWin32ClientRect(self->handle);

    x = pClamp(x, 0, rect.right - rect.left);
    y = pClamp(y, 0, rect.bottom - rect.top);

    width  = pClamp(pMin(width, rect.right - rect.left - x), 0, bitmap->width);
    height = pClamp(pMin(height, rect.bottom - rect.top - y), 0, bitmap->height);

    StretchDIBits(self->back_context, x, y, width, height, 0, 0, width, height,
        bitmap->pntr, &bitmap->info, DIB_RGB_COLORS, SRCCOPY);
}

void pWin32WindowFlush(PWin32Window* self)
{
    HDC     context = self->back_context;
    HBITMAP buffer  = self->back_buffer;

    self->back_context  = self->front_context;
    self->front_context = context;

    self->back_buffer  = self->front_buffer;
    self->front_buffer = buffer;

    InvalidateRect(self->handle, NULL, 0);
}

b32 pWin32WindowPollEvent(PWin32Window* self, PWindowEvent* event)
{
    MSG message;

    while (PeekMessageW(&message, 0, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);

        switch (message.message) {
            case WM_QUIT: *event = pWindowEventQuit(self); return 1;

            case WM_CREATE:  *event = pWindowEventWindowCreate(self);  return 1;
            case WM_DESTROY: *event = pWindowEventWindowDestroy(self); return 1;

            case WM_KEYDOWN: {
                PWindowKeyboardKey key  = pWin32WindowConvertKey(message.wParam);
                ssize               scan = (message.lParam >> 16) & 0xff;

                *event = pWindowEventKeyboardKey(self, key, 1, scan);
            } return 1;

            case WM_KEYUP: {
                PWindowKeyboardKey key  = pWin32WindowConvertKey(message.wParam);
                ssize               scan = (message.lParam >> 16) & 0xff;

                *event = pWindowEventKeyboardKey(self, key, 0, scan);
            } return 1;

            default: break;
        }
    }

    return 0;
}

ssize pWin32WindowWidthSet(PWin32Window* self, ssize width)
{
    RECT rect = pWin32WindowRect(self->handle);

    ssize result = rect.right - rect.left;

    width = pClamp(width, self->width_min, self->width_max);

    MoveWindow(self->handle, rect.left, rect.top,
        width, rect.bottom - rect.top, 1);

    return result;
}

ssize pWin32WindowWidthGet(PWin32Window* self)
{
    RECT rect = pWin32ClientRect(self->handle);

    return rect.right - rect.left;
}

ssize pWin32WindowHeightSet(PWin32Window* self, ssize height)
{
    RECT rect = pWin32WindowRect(self->handle);

    ssize result = rect.bottom - rect.top;

    height = pClamp(height, self->height_min, self->height_max);

    MoveWindow(self->handle, rect.left, rect.top,
        rect.right - rect.left, height, 1);

    return result;
}

ssize pWin32WindowHeightGet(PWin32Window* self)
{
    RECT rect = pWin32ClientRect(self->handle);

    return rect.bottom - rect.top;
}

void* pWin32WindowPntrContextSet(PWin32Window* self, void* ctxt)
{
    void* result = self->ctxt;

    self->ctxt = ctxt;

    return result;
}

void* pWin32WindowPntrContextGet(PWin32Window* self)
{
    return self->ctxt;
}

void* pWin32WindowProcUpdateSet(PWin32Window* self, void* proc)
{
    void* result = self->proc_update;

    self->proc_update = proc;

    return result;
}

void* pWin32WindowProcUpdateGet(PWin32Window* self)
{
    return self->proc_update;
}

b32 pWin32WindowVisibilitySet(PWin32Window* self, PWindowVisibility visibility)
{
    switch (visibility) {
        case PWindowVisibility_Hide: ShowWindow(self->handle, SW_HIDE); break;
        case PWindowVisibility_Show: ShowWindow(self->handle, SW_SHOW); break;

        default: return 0;
    }

    UpdateWindow(self->handle);

    return 1;
}

 PWindowVisibility pWin32WindowVisibilityGet(PWin32Window* self)
{
    return PWindowVisibility_None;
}

#endif // P_WI32_WINDOW_WINDOW_C
