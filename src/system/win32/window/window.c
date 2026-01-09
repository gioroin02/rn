#ifndef PX_WIN32_WINDOW_WINDOW_C
#define PX_WIN32_WINDOW_WINDOW_C

#include "window.h"

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
        case WM_NCLBUTTONDOWN: {
            ssize mode = wparam;

            if (mode == HTCAPTION || (mode >= HTLEFT && mode <= HTBOTTOMRIGHT)) {
                self->drag_mode   = mode;
                self->drag_cursor = pxWin32CursorPoint(self->handle);
                self->drag_window = pxWin32WindowRect(self->handle);

                SetCapture(self->handle);
            }
            else result = -1;
        } break;

        case WM_LBUTTONUP: {
            if (GetCapture() == handle)
                ReleaseCapture();
            else
                result = -1;
        } break;

        case WM_CAPTURECHANGED: self->drag_mode = 0; break;

        case WM_MOUSEMOVE: {
            if (GetCapture() == handle && self->drag_mode != 0) {
                POINT point = pxWin32CursorPoint(handle);
                RECT  rect  = self->drag_window;

                ssize delta_x = point.x - self->drag_cursor.x;
                ssize delta_y = point.y - self->drag_cursor.y;

                switch (self->drag_mode) {
                    case HTCAPTION: OffsetRect(&rect, delta_x, delta_y); break;

                    case HTLEFT:   rect.left   += delta_x; break;
                    case HTTOP:    rect.top    += delta_y; break;
                    case HTBOTTOM: rect.bottom += delta_y; break;
                    case HTRIGHT:  rect.right  += delta_x; break;

                    case HTTOPLEFT:    rect.left += delta_x; rect.top    += delta_y; break;
                    case HTBOTTOMLEFT: rect.left += delta_x; rect.bottom += delta_y; break;

                    case HTTOPRIGHT:    rect.right += delta_x; rect.top    += delta_y; break;
                    case HTBOTTOMRIGHT: rect.right += delta_x; rect.bottom += delta_y; break;

                    default: break;
                }

                ssize left   = rect.left;
                ssize top    = rect.top;
                ssize width  = pxMax(rect.right - rect.left, 200);
                ssize height = pxMax(rect.bottom - rect.top, 150);

                SetWindowPos(handle, PX_NULL, left, top, width, height,
                    SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            }
            else result = -1;
        } break;

        case WM_SIZE: {
            RECT rect = pxWin32ClientRect(handle);

            if (self->back_surface != PX_NULL) DeleteObject(self->back_surface);

            self->back_surface = CreateCompatibleBitmap(self->back_context,
                rect.right - rect.left, rect.bottom - rect.top);

            SelectObject(self->back_context, self->back_surface);

            InvalidateRect(handle, PX_NULL, 0);

            result = -1;
        } break;

        /* case WM_SYSCOMMAND: {
            POINT point = pxWin32CursorPoint(handle);
            UINT  cmd   = wparam & 0xFFF0;

            if (cmd == SC_MOVE || cmd == SC_SIZE) {
            }
            else result = -1;
        } break; */

        case WM_ERASEBKGND: {
            RECT rect = pxWin32ClientRect(handle);

            u8 red   = (u8) (self->back_color & ((u32) 0x0000FF) >> 0);
            u8 green = (u8) (self->back_color & ((u32) 0x00FF00) >> 8);
            u8 blue  = (u8) (self->back_color & ((u32) 0xFF0000) >> 16);

            SetDCBrushColor(self->back_context, RGB(red, green, blue));

            FillRect(self->back_context, &rect, GetStockObject(DC_BRUSH));

            result = 1;
        } break;

        case WM_PAINT: {
            PAINTSTRUCT paint;

            RECT rect    = pxWin32ClientRect(handle);
            HDC  context = BeginPaint(handle, &paint);

            ssize width  = rect.right - rect.left;
            ssize height = rect.bottom - rect.top;

            BitBlt(context, 0, 0, width, height, self->back_context, 0, 0, SRCCOPY);

            EndPaint(handle, &paint);
        } break;

        case WM_CLOSE: case WM_DESTROY: PostQuitMessage(0); break;

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

    PxString16 string = pxWin32Str8ToStr16(buffer, sizeof buffer, title);
    DWORD      style  = WS_OVERLAPPEDWINDOW;
    RECT       rect   = pxWin32RectAdjusted(0, 0, width, height);

    if (string.size <= 0 || pxWin32WindowStart() == 0) return 0;

    HWND handle = CreateWindowExW(0, L"PxWindowRegular", string.values,
        style, CW_USEDEFAULT, CW_USEDEFAULT, rect.right, rect.bottom,
        PX_NULL, PX_NULL, GetModuleHandle(PX_NULL), PX_NULL);

    if (handle != PX_NULL) {
        HDC  context = GetDC(self->handle);

        self->handle       = handle;
        self->back_context = CreateCompatibleDC(context);
        self->back_color   = 0;
        self->drag_mode    = 0;
        self->drag_cursor  = pxWin32Point(0, 0);
        self->drag_window  = pxWin32Rect(0, 0, 0, 0);

        ReleaseDC(self->handle, context);

        RECT rect = pxWin32ClientRect(self->handle);

        self->back_surface = CreateCompatibleBitmap(self->back_context,
            rect.right - rect.left, rect.bottom - rect.top);

        SelectObject(self->back_context, self->back_surface);

        SetWindowLongPtr(self->handle, GWLP_USERDATA, (LONG_PTR) self);

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

        DeleteObject(self->back_surface);
        DeleteObject(self->back_context);

        DestroyWindow(self->handle);
    }

    pxMemorySet(self, sizeof *self, 0xAB);

    pxWin32WindowStop();
}

void pxWin32WindowClear(PxWin32Window* self)
{
    InvalidateRect(self->handle, PX_NULL, 0);
}

void pxWin32WindowFlush(PxWin32Window* self, PxWin32WindowSurface* surface)
{
    // TODO(Gio): Render to back buffer...
}

b32 pxWin32WindowPollEvent(PxWin32Window* self, PxWindowEvent* event)
{
    PxWindowEvent temp;
    MSG           message;

    while (PeekMessageW(&message, 0, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);

        switch (message.message) {
            case WM_QUIT: temp = pxWindowEventQuit(); break;

            case WM_KEYDOWN: {
                PxWindowKeyboardKey key  = pxWin32WindowConvertKey(message.wParam);
                ssize               scan = (message.lParam >> 16) & 0xff;

                temp = pxWindowEventKeyboardKey(key, 1, scan);
            } break;

            case WM_KEYUP: {
                PxWindowKeyboardKey key  = pxWin32WindowConvertKey(message.wParam);
                ssize               scan = (message.lParam >> 16) & 0xff;

                temp = pxWindowEventKeyboardKey(key, 0, scan);
            } break;

            default: break;
        }

        if (temp.kind != PxWindowEvent_None) {
            if (event != PX_NULL)
                *event = temp;

            return 1;
        }
    }

    return 0;
}

void pxWin32WindowClearColorSet(PxWin32Window* self, u8 red, u8 green, u8 blue, u8 alpha)
{
    u32 color = ((u32) red)   << 0
              | ((u32) green) << 8
              | ((u32) blue)  << 16
              | ((u32) alpha) << 24;

    self->back_color = color;
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

#endif // PX_WI32_WINDOW_WINDOW_C
