#ifndef P_SYSTEM_WIN32_WINDOW_WINDOW_C
#define P_SYSTEM_WIN32_WINDOW_WINDOW_C

#include "window.h"

#define P_SYSTEM_WIN32_TIMER_RESIZE ((Int) 1)

static POINT pWin32Point(Int x, Int y)
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

static RECT pWin32Rect(Int x, Int y, Int w, Int h)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.left   = x;
    result.top    = y;
    result.right  = x + w;
    result.bottom = y + h;

    return result;
}

static RECT pWin32RectAdjusted(Int x, Int y, Int w, Int h)
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

static PString16 pWin32Str8ToStr16(U16* pntr, Int size, PString8 string)
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

Int pWin32WindowProcRegular(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    PWin32Window* self = (PWin32Window*) GetWindowLongPtr(handle, GWLP_USERDATA);

    if (self == NULL) return DefWindowProcW(handle, kind, wparam, lparam);

    Int result = 0;

    switch (kind) {
        case WM_ENTERSIZEMOVE:
            SetTimer(handle, P_SYSTEM_WIN32_TIMER_RESIZE, 10, NULL);
        break;

        case WM_EXITSIZEMOVE:
            KillTimer(handle, P_SYSTEM_WIN32_TIMER_RESIZE);
        break;

        case WM_TIMER: {
            if (wparam == P_SYSTEM_WIN32_TIMER_RESIZE) {
                if (self->paint_proc != NULL) {
                    PWin32FrameBuffer* buffer = pWin32WindowGetBuffer(self);

                    ((PWindowCallback*) self->paint_proc)(
                        self->paint_ctxt, (PWindow*) self, (PFrameBuffer*) buffer);

                    pWin32WindowFlushBuffer(self);
                }
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

            Int left   = paint.rcPaint.left;
            Int top    = paint.rcPaint.top;
            Int width  = paint.rcPaint.right - paint.rcPaint.left;
            Int height = paint.rcPaint.bottom - paint.rcPaint.top;

            BitBlt(context, left, top, width, height,
                self->context, left, top, SRCCOPY);

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

Bool pWin32WindowCreate(PWin32Window* self, PString8 title, Int width, Int height)
{
    static U16 buffer[P_MEMORY_KIB];

    if (width <= 0 || height <= 0 || width > P_INT_MAX / height) return 0;

    RECT      rect   = pWin32RectAdjusted(0, 0, width, height);
    PString16 string = pWin32Str8ToStr16(buffer, sizeof buffer, title);

    if (string.size <= 0 || pWin32WindowStart() == 0) return 0;

    width  = rect.right - rect.left;
    height = rect.bottom - rect.top;

    HDC context = CreateCompatibleDC(NULL);

    if (context == NULL) return 0;

    HWND handle = CreateWindowW(L"PWindowRegular", string.values, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, NULL, NULL);

    if (handle != NULL) {
        self->handle     = handle;
        self->context    = context;
        self->width_max  = 1920;
        self->width_min  = 320;
        self->height_max = 1080;
        self->height_min = 180;
        self->paint_ctxt = NULL;
        self->paint_proc = NULL;

        pWin32FrameBufferCreate(&self->buffer_front,
            self->width_max, self->height_max);

        pWin32FrameBufferCreate(&self->buffer_back,
            self->width_max, self->height_max);

        SelectObject(self->context, self->buffer_front.bitmap);

        SetWindowLongPtr(self->handle, GWLP_USERDATA, (LONG_PTR) self);

        InvalidateRect(self->handle, NULL, 0);
        UpdateWindow(self->handle);

        return 1;
    }

    DeleteDC(context);

    pWin32WindowStop();

    return 0;
}

void pWin32WindowDestroy(PWin32Window* self)
{
    if (self->handle != NULL) {
        pWin32FrameBufferDestroy(&self->buffer_back);
        pWin32FrameBufferDestroy(&self->buffer_front);

        DeleteDC(self->context);

        DestroyWindow(self->handle);
    }

    pMemorySet(self, sizeof *self, 0xAB);

    pWin32WindowStop();
}

Bool pWin32WindowPollEvent(PWin32Window* self, PWindowEvent* event)
{
    MSG message;

    while (PeekMessageW(&message, 0, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);

        switch (message.message) {
            case WM_QUIT: *event = pWindowEventQuit((PWindow*) self); return 1;

            case WM_CREATE:  *event = pWindowEventWindowCreate((PWindow*) self);  return 1;
            case WM_DESTROY: *event = pWindowEventWindowDestroy((PWindow*) self); return 1;

            case WM_KEYDOWN: {
                PWindowKeyboardKey key  = pWin32WindowConvertKey(message.wParam);
                Int               scan = (message.lParam >> 16) & 0xff;

                *event = pWindowEventKeyboardKey((PWindow*) self, key, 1, scan);
            } return 1;

            case WM_KEYUP: {
                PWindowKeyboardKey key  = pWin32WindowConvertKey(message.wParam);
                Int               scan = (message.lParam >> 16) & 0xff;

                *event = pWindowEventKeyboardKey((PWindow*) self, key, 0, scan);
            } return 1;

            default: break;
        }
    }

    return 0;
}

PWin32FrameBuffer* pWin32WindowGetBuffer(PWin32Window* self)
{
    return &self->buffer_back;
}

void pWin32WindowFlushBuffer(PWin32Window* self)
{
    PWin32FrameBuffer temp = self->buffer_front;

    self->buffer_front = self->buffer_back;
    self->buffer_back  = temp;

    SelectObject(self->context, self->buffer_front.bitmap);

    InvalidateRect(self->handle, NULL, 0);
    UpdateWindow(self->handle);
}

Bool pWin32WindowSetVisibility(PWin32Window* self, PWindowVisibility visibility)
{
    switch (visibility) {
        case PWindowVisibility_Hide: ShowWindow(self->handle, SW_HIDE); break;
        case PWindowVisibility_Show: ShowWindow(self->handle, SW_SHOW); break;

        default: return 0;
    }

    return 1;
}

 PWindowVisibility pWin32WindowGetVisibility(PWin32Window* self)
{
    return PWindowVisibility_None;
}

Bool pWin32WindowSetCallback(PWin32Window* self, void* ctxt, void* proc)
{
    self->paint_ctxt = ctxt;
    self->paint_proc = proc;

    return 1;
}

void* pWin32WindowGetCallback(PWin32Window* self)
{
    return self->paint_proc;
}

/*
Int pWin32WindowWidthSet(PWin32Window* self, Int width)
{
    RECT rect = pWin32WindowRect(self->handle);

    Int result = rect.right - rect.left;

    width = pClamp(width, self->width_min, self->width_max);

    MoveWindow(self->handle, rect.left, rect.top,
        width, rect.bottom - rect.top, 1);

    return result;
}

Int pWin32WindowWidthGet(PWin32Window* self)
{
    RECT rect = pWin32ClientRect(self->handle);

    return rect.right - rect.left;
}

Int pWin32WindowHeightSet(PWin32Window* self, Int height)
{
    RECT rect = pWin32WindowRect(self->handle);

    Int result = rect.bottom - rect.top;

    height = pClamp(height, self->height_min, self->height_max);

    MoveWindow(self->handle, rect.left, rect.top,
        rect.right - rect.left, height, 1);

    return result;
}

Int pWin32WindowHeightGet(PWin32Window* self)
{
    RECT rect = pWin32ClientRect(self->handle);

    return rect.bottom - rect.top;
}
*/

#endif // P_WI32_WINDOW_WINDOW_C
