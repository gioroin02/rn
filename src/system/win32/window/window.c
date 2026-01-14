#ifndef PX_WIN32_WINDOW_WINDOW_C
#define PX_WIN32_WINDOW_WINDOW_C

#include "window.h"

#define PX_WIN32_TIMER_RESIZE ((ssize) 1)

static POINT pxWin32Point(ssize x, ssize y)
{
    POINT result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.x = x;
    result.y = y;

    return result;
}

static POINT pxWin32CursorPoint(HWND handle)
{
    POINT result;

    pxMemorySet(&result, sizeof result, 0xAB);

    GetCursorPos(&result);

    return result;
}

static RECT pxWin32Rect(ssize x, ssize y, ssize w, ssize h)
{
    RECT result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.left   = x;
    result.top    = y;
    result.right  = x + w;
    result.bottom = y + h;

    return result;
}

static RECT pxWin32RectAdjusted(ssize x, ssize y, ssize w, ssize h)
{
    RECT result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.left   = x;
    result.top    = y;
    result.right  = x + w;
    result.bottom = y + h;

    AdjustWindowRect(&result, 0, 0);

    return result;
}

static RECT pxWin32WindowRect(HWND handle)
{
    RECT result;

    pxMemorySet(&result, sizeof result, 0xAB);

    GetWindowRect(handle, &result);

    return result;
}

static RECT pxWin32ClientRect(HWND handle)
{
    RECT result;

    pxMemorySet(&result, sizeof result, 0xAB);

    GetClientRect(handle, &result);

    return result;
}

static PxString16 pxWin32Str8ToStr16(u16* pntr, ssize size, PxString8 string)
{
    PxString16 result = pxString16Make(PX_NULL, 0);

     size = MultiByteToWideChar(CP_UTF8, 0,
        (char*) string.values, string.size, (LPWSTR) pntr, size);

     if (size > 0) result = pxString16Make(pntr, size);

     return result;
}

static PxWindowKeyboardKey pxWin32WindowConvertKey(WORD key_code)
{
    switch (key_code) {
        case 'A':            return PxWindowKeyboardKey_A;            break;
        case 'B':            return PxWindowKeyboardKey_B;            break;
        case 'C':            return PxWindowKeyboardKey_C;            break;
        case 'D':            return PxWindowKeyboardKey_D;            break;
        case 'E':            return PxWindowKeyboardKey_E;            break;
        case 'F':            return PxWindowKeyboardKey_F;            break;
        case 'G':            return PxWindowKeyboardKey_G;            break;
        case 'H':            return PxWindowKeyboardKey_H;            break;
        case 'I':            return PxWindowKeyboardKey_I;            break;
        case 'J':            return PxWindowKeyboardKey_J;            break;
        case 'K':            return PxWindowKeyboardKey_K;            break;
        case 'L':            return PxWindowKeyboardKey_L;            break;
        case 'M':            return PxWindowKeyboardKey_M;            break;
        case 'N':            return PxWindowKeyboardKey_N;            break;
        case 'O':            return PxWindowKeyboardKey_O;            break;
        case 'P':            return PxWindowKeyboardKey_P;            break;
        case 'Q':            return PxWindowKeyboardKey_Q;            break;
        case 'R':            return PxWindowKeyboardKey_R;            break;
        case 'S':            return PxWindowKeyboardKey_S;            break;
        case 'T':            return PxWindowKeyboardKey_T;            break;
        case 'U':            return PxWindowKeyboardKey_U;            break;
        case 'V':            return PxWindowKeyboardKey_V;            break;
        case 'W':            return PxWindowKeyboardKey_W;            break;
        case 'X':            return PxWindowKeyboardKey_X;            break;
        case 'Y':            return PxWindowKeyboardKey_Y;            break;
        case 'Z':            return PxWindowKeyboardKey_Z;            break;
        case '0':            return PxWindowKeyboardKey_0;            break;
        case '1':            return PxWindowKeyboardKey_1;            break;
        case '2':            return PxWindowKeyboardKey_2;            break;
        case '3':            return PxWindowKeyboardKey_3;            break;
        case '4':            return PxWindowKeyboardKey_4;            break;
        case '5':            return PxWindowKeyboardKey_5;            break;
        case '6':            return PxWindowKeyboardKey_6;            break;
        case '7':            return PxWindowKeyboardKey_7;            break;
        case '8':            return PxWindowKeyboardKey_8;            break;
        case '9':            return PxWindowKeyboardKey_9;            break;
        case VK_SPACE:       return PxWindowKeyboardKey_Space;        break;
        case VK_OEM_MINUS:   return PxWindowKeyboardKey_Minus;        break;
        case VK_OEM_PLUS:    return PxWindowKeyboardKey_Equal;        break;
        case VK_OEM_4:       return PxWindowKeyboardKey_SquareLeft;   break;
        case VK_OEM_6:       return PxWindowKeyboardKey_SquareRight;  break;
        case VK_OEM_5:       return PxWindowKeyboardKey_BackSlash;    break;
        case VK_OEM_1:       return PxWindowKeyboardKey_SemiColon;    break;
        case VK_OEM_7:       return PxWindowKeyboardKey_Apostrophe;   break;
        case VK_OEM_3:       return PxWindowKeyboardKey_Grave;        break;
        case VK_OEM_COMMA:   return PxWindowKeyboardKey_Comma;        break;
        case VK_OEM_PERIOD:  return PxWindowKeyboardKey_Period;       break;
        case VK_OEM_2:       return PxWindowKeyboardKey_Slash;        break;
        case VK_UP:          return PxWindowKeyboardKey_Up;           break;
        case VK_DOWN:        return PxWindowKeyboardKey_Down;         break;
        case VK_LEFT:        return PxWindowKeyboardKey_Left;         break;
        case VK_RIGHT:       return PxWindowKeyboardKey_Right;        break;
        case VK_HOME:        return PxWindowKeyboardKey_Home;         break;
        case VK_END:         return PxWindowKeyboardKey_End;          break;
        case VK_PRIOR:       return PxWindowKeyboardKey_PageUp;       break;
        case VK_NEXT:        return PxWindowKeyboardKey_PageDown;     break;
        case VK_INSERT:      return PxWindowKeyboardKey_Insert;       break;
        case VK_DELETE:      return PxWindowKeyboardKey_Delete;       break;
        case VK_F1:          return PxWindowKeyboardKey_F1;           break;
        case VK_F2:          return PxWindowKeyboardKey_F2;           break;
        case VK_F3:          return PxWindowKeyboardKey_F3;           break;
        case VK_F4:          return PxWindowKeyboardKey_F4;           break;
        case VK_F5:          return PxWindowKeyboardKey_F5;           break;
        case VK_F6:          return PxWindowKeyboardKey_F6;           break;
        case VK_F7:          return PxWindowKeyboardKey_F7;           break;
        case VK_F8:          return PxWindowKeyboardKey_F8;           break;
        case VK_F9:          return PxWindowKeyboardKey_F9;           break;
        case VK_F10:         return PxWindowKeyboardKey_F10;          break;
        case VK_F11:         return PxWindowKeyboardKey_F11;          break;
        case VK_F12:         return PxWindowKeyboardKey_F12;          break;
        case VK_RETURN:      return PxWindowKeyboardKey_Enter;        break;
        case VK_ESCAPE:      return PxWindowKeyboardKey_Escape;       break;
        case VK_BACK:        return PxWindowKeyboardKey_BackSpace;    break;
        case VK_TAB:         return PxWindowKeyboardKey_Tab;          break;

        default: break;
    }

    return PxWindowKeyboardKey_None;
}

ssize pxWin32WindowProc(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    PxWin32Window* self = (PxWin32Window*) GetWindowLongPtr(handle, GWLP_USERDATA);

    if (self == PX_NULL) return DefWindowProcW(handle, kind, wparam, lparam);

    ssize result = 0;

    switch (kind) {
        case WM_ENTERSIZEMOVE:
            SetTimer(handle, PX_WIN32_TIMER_RESIZE, 10, PX_NULL);
        break;

        case WM_EXITSIZEMOVE: KillTimer(handle, PX_WIN32_TIMER_RESIZE); break;

        case WM_TIMER: {
            if (wparam == PX_WIN32_TIMER_RESIZE) {
                if (self->proc_update != PX_NULL)
                    ((PxWindowProcUpdate*) self->proc_update)(self->ctxt);
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

PxWin32Window* pxWin32WindowReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32Window);
}

b32
pxWin32WindowCreate(PxWin32Window* self, PxString8 title, ssize width, ssize height)
{
    static u16 buffer[PX_MEMORY_KIB];

    if (width <= 0 || height <= 0 || width > PX_SSIZE_MAX / height) return 0;

    RECT       rect   = pxWin32RectAdjusted(0, 0, width, height);
    PxString16 string = pxWin32Str8ToStr16(buffer, sizeof buffer, title);

    if (string.size <= 0 || pxWin32WindowStart() == 0) return 0;

    width  = rect.right - rect.left;
    height = rect.bottom - rect.top;

    HWND handle = CreateWindowW(L"PxWindowRegular",
        string.values, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        width, height, PX_NULL, PX_NULL, PX_NULL, PX_NULL);

    if (handle != PX_NULL) {
        self->handle        = handle;
        self->front_context = PX_NULL;
        self->front_buffer  = PX_NULL;
        self->back_context  = PX_NULL;
        self->back_buffer   = PX_NULL;
        self->draw_color    = 0;
        self->ctxt          = PX_NULL;
        self->proc_update   = PX_NULL;
        self->width_max     = 1920;
        self->width_min     = 320;
        self->height_max    = 1080;
        self->height_min    = 180;

        SetWindowLongPtr(self->handle, GWLP_USERDATA, (LONG_PTR) self);

        RECT rect    = pxWin32ClientRect(self->handle);
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

        InvalidateRect(self->handle, PX_NULL, 0);

        return 1;
    }

    pxWin32WindowStop();

    return 0;
}

void pxWin32WindowDestroy(PxWin32Window* self)
{
    if (self->handle != PX_NULL) {
        if (GetCapture() == self->handle)
            ReleaseCapture();

        DeleteObject(self->back_buffer);
        DeleteObject(self->front_buffer);

        DeleteDC(self->back_context);
        DeleteDC(self->front_context);

        DestroyWindow(self->handle);
    }

    pxMemorySet(self, sizeof *self, 0xAB);

    pxWin32WindowStop();
}

void pxWin32WindowClear(PxWin32Window* self, u8 red, u8 green, u8 blue)
{
    RECT rect = pxWin32ClientRect(self->handle);

    u32 color = ((u32) red)   << 0
              | ((u32) green) << 8
              | ((u32) blue)  << 16;

    self->draw_color = color;

    SetDCBrushColor(self->back_context, RGB(red, green, blue));
    FillRect(self->back_context, &rect, GetStockObject(DC_BRUSH));

    InvalidateRect(self->handle, PX_NULL, 0);
}

void pxWin32WindowPaint(PxWin32Window* self, ssize x, ssize y, ssize width, ssize height, PxWin32Bitmap* bitmap)
{
    if (self->back_buffer == PX_NULL || bitmap == PX_NULL) return;

    RECT rect = pxWin32ClientRect(self->handle);

    x = pxClamp(x, 0, rect.right - rect.left);
    y = pxClamp(y, 0, rect.bottom - rect.top);

    width  = pxClamp(pxMin(width, rect.right - rect.left - x), 0, bitmap->width);
    height = pxClamp(pxMin(height, rect.bottom - rect.top - y), 0, bitmap->height);

    StretchDIBits(self->back_context, x, y, width, height, 0, 0, width, height,
        bitmap->pntr, &bitmap->info, DIB_RGB_COLORS, SRCCOPY);
}

void pxWin32WindowFlush(PxWin32Window* self)
{
    HDC     context = self->back_context;
    HBITMAP buffer  = self->back_buffer;

    self->back_context  = self->front_context;
    self->front_context = context;

    self->back_buffer  = self->front_buffer;
    self->front_buffer = buffer;

    InvalidateRect(self->handle, PX_NULL, 0);
}

b32 pxWin32WindowPollEvent(PxWin32Window* self, PxWindowEvent* event)
{
    MSG message;

    while (PeekMessageW(&message, 0, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);

        switch (message.message) {
            case WM_QUIT: *event = pxWindowEventQuit(self); return 1;

            case WM_CREATE:  *event = pxWindowEventWindowCreate(self);  return 1;
            case WM_DESTROY: *event = pxWindowEventWindowDestroy(self); return 1;

            case WM_KEYDOWN: {
                PxWindowKeyboardKey key  = pxWin32WindowConvertKey(message.wParam);
                ssize               scan = (message.lParam >> 16) & 0xff;

                *event = pxWindowEventKeyboardKey(self, key, 1, scan);
            } return 1;

            case WM_KEYUP: {
                PxWindowKeyboardKey key  = pxWin32WindowConvertKey(message.wParam);
                ssize               scan = (message.lParam >> 16) & 0xff;

                *event = pxWindowEventKeyboardKey(self, key, 0, scan);
            } return 1;

            default: break;
        }
    }

    return 0;
}

ssize pxWin32WindowWidthSet(PxWin32Window* self, ssize width)
{
    RECT rect = pxWin32WindowRect(self->handle);

    ssize result = rect.right - rect.left;

    width = pxClamp(width, self->width_min, self->width_max);

    MoveWindow(self->handle, rect.left, rect.top,
        width, rect.bottom - rect.top, 1);

    return result;
}

ssize pxWin32WindowWidthGet(PxWin32Window* self)
{
    RECT rect = pxWin32ClientRect(self->handle);

    return rect.right - rect.left;
}

ssize pxWin32WindowHeightSet(PxWin32Window* self, ssize height)
{
    RECT rect = pxWin32WindowRect(self->handle);

    ssize result = rect.bottom - rect.top;

    height = pxClamp(height, self->height_min, self->height_max);

    MoveWindow(self->handle, rect.left, rect.top,
        rect.right - rect.left, height, 1);

    return result;
}

ssize pxWin32WindowHeightGet(PxWin32Window* self)
{
    RECT rect = pxWin32ClientRect(self->handle);

    return rect.bottom - rect.top;
}

void* pxWin32WindowPntrContextSet(PxWin32Window* self, void* ctxt)
{
    void* result = self->ctxt;

    self->ctxt = ctxt;

    return result;
}

void* pxWin32WindowPntrContextGet(PxWin32Window* self)
{
    return self->ctxt;
}

void* pxWin32WindowProcUpdateSet(PxWin32Window* self, void* proc)
{
    void* result = self->proc_update;

    self->proc_update = proc;

    return result;
}

void* pxWin32WindowProcUpdateGet(PxWin32Window* self)
{
    return self->proc_update;
}

b32 pxWin32WindowVisibilitySet(PxWin32Window* self, PxWindowVisibility visibility)
{
    switch (visibility) {
        case PxWindowVisibility_Hide: ShowWindow(self->handle, SW_HIDE); break;
        case PxWindowVisibility_Show: ShowWindow(self->handle, SW_SHOW); break;

        default: return 0;
    }

    UpdateWindow(self->handle);

    return 1;
}

 PxWindowVisibility pxWin32WindowVisibilityGet(PxWin32Window* self)
{
    return PxWindowVisibility_None;
}

#endif // PX_WI32_WINDOW_WINDOW_C
