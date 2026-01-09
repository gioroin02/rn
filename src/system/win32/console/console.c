#ifndef PX_WIN32_CONSOLE_CONSOLE_C
#define PX_WIN32_CONSOLE_CONSOLE_C

#include "console.h"

static PxConsoleKeyboardKey pxWin32ConsoleConvertKey(WORD key_code, CHAR key_char)
{
    switch (key_char) {
        case 'a': return PxConsoleKeyboardKey_A; break;
        case 'b': return PxConsoleKeyboardKey_B; break;
        case 'c': return PxConsoleKeyboardKey_C; break;
        case 'd': return PxConsoleKeyboardKey_D; break;
        case 'e': return PxConsoleKeyboardKey_E; break;
        case 'f': return PxConsoleKeyboardKey_F; break;
        case 'g': return PxConsoleKeyboardKey_G; break;
        case 'h': return PxConsoleKeyboardKey_H; break;
        case 'i': return PxConsoleKeyboardKey_I; break;
        case 'j': return PxConsoleKeyboardKey_J; break;
        case 'k': return PxConsoleKeyboardKey_K; break;
        case 'l': return PxConsoleKeyboardKey_L; break;
        case 'm': return PxConsoleKeyboardKey_M; break;
        case 'n': return PxConsoleKeyboardKey_N; break;
        case 'o': return PxConsoleKeyboardKey_O; break;
        case 'p': return PxConsoleKeyboardKey_P; break;
        case 'q': return PxConsoleKeyboardKey_Q; break;
        case 'r': return PxConsoleKeyboardKey_R; break;
        case 's': return PxConsoleKeyboardKey_S; break;
        case 't': return PxConsoleKeyboardKey_T; break;
        case 'u': return PxConsoleKeyboardKey_U; break;
        case 'v': return PxConsoleKeyboardKey_V; break;
        case 'w': return PxConsoleKeyboardKey_W; break;
        case 'x': return PxConsoleKeyboardKey_X; break;
        case 'y': return PxConsoleKeyboardKey_Y; break;
        case 'z': return PxConsoleKeyboardKey_Z; break;
        case '0': return PxConsoleKeyboardKey_0; break;
        case '1': return PxConsoleKeyboardKey_1; break;
        case '2': return PxConsoleKeyboardKey_2; break;
        case '3': return PxConsoleKeyboardKey_3; break;
        case '4': return PxConsoleKeyboardKey_4; break;
        case '5': return PxConsoleKeyboardKey_5; break;
        case '6': return PxConsoleKeyboardKey_6; break;
        case '7': return PxConsoleKeyboardKey_7; break;
        case '8': return PxConsoleKeyboardKey_8; break;
        case '9': return PxConsoleKeyboardKey_9; break;

        default: break;
    }

    switch (key_code) {
        case VK_SPACE:       return PxConsoleKeyboardKey_Space;        break;
        case VK_OEM_MINUS:   return PxConsoleKeyboardKey_Minus;        break;
        case VK_OEM_PLUS:    return PxConsoleKeyboardKey_Equal;        break;
        case VK_OEM_4:       return PxConsoleKeyboardKey_SquareLeft;   break;
        case VK_OEM_6:       return PxConsoleKeyboardKey_SquareRight;  break;
        case VK_OEM_5:       return PxConsoleKeyboardKey_BackSlash;    break;
        case VK_OEM_1:       return PxConsoleKeyboardKey_SemiColon;    break;
        case VK_OEM_7:       return PxConsoleKeyboardKey_Apostrophe;   break;
        case VK_OEM_3:       return PxConsoleKeyboardKey_Grave;        break;
        case VK_OEM_COMMA:   return PxConsoleKeyboardKey_Comma;        break;
        case VK_OEM_PERIOD:  return PxConsoleKeyboardKey_Period;       break;
        case VK_OEM_2:       return PxConsoleKeyboardKey_Slash;        break;
        case VK_UP:          return PxConsoleKeyboardKey_Up;           break;
        case VK_DOWN:        return PxConsoleKeyboardKey_Down;         break;
        case VK_LEFT:        return PxConsoleKeyboardKey_Left;         break;
        case VK_RIGHT:       return PxConsoleKeyboardKey_Right;        break;
        case VK_HOME:        return PxConsoleKeyboardKey_Home;         break;
        case VK_END:         return PxConsoleKeyboardKey_End;          break;
        case VK_PRIOR:       return PxConsoleKeyboardKey_PageUp;       break;
        case VK_NEXT:        return PxConsoleKeyboardKey_PageDown;     break;
        case VK_INSERT:      return PxConsoleKeyboardKey_Insert;       break;
        case VK_DELETE:      return PxConsoleKeyboardKey_Delete;       break;
        case VK_F1:          return PxConsoleKeyboardKey_F1;           break;
        case VK_F2:          return PxConsoleKeyboardKey_F2;           break;
        case VK_F3:          return PxConsoleKeyboardKey_F3;           break;
        case VK_F4:          return PxConsoleKeyboardKey_F4;           break;
        case VK_F5:          return PxConsoleKeyboardKey_F5;           break;
        case VK_F6:          return PxConsoleKeyboardKey_F6;           break;
        case VK_F7:          return PxConsoleKeyboardKey_F7;           break;
        case VK_F8:          return PxConsoleKeyboardKey_F8;           break;
        case VK_F9:          return PxConsoleKeyboardKey_F9;           break;
        case VK_F10:         return PxConsoleKeyboardKey_F10;          break;
        case VK_F11:         return PxConsoleKeyboardKey_F11;          break;
        case VK_F12:         return PxConsoleKeyboardKey_F12;          break;
        case VK_RETURN:      return PxConsoleKeyboardKey_Enter;        break;
        case VK_ESCAPE:      return PxConsoleKeyboardKey_Escape;       break;
        case VK_BACK:        return PxConsoleKeyboardKey_BackSpace;    break;
        case VK_TAB:         return PxConsoleKeyboardKey_Tab;          break;

        default: break;
    }

    return PxConsoleKeyboardKey_None;
}

static b32 pxWin32ConsoleModeSetCooked(PxWin32Console* self)
{
    if (self->mode != PxConsoleMode_Cooked) {
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), self->conf_in);
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), self->conf_out);

        self->mode = PxConsoleMode_Cooked;
    }

    return 1;
}

static b32 pxWin32ConsoleModeSetRaw(PxWin32Console* self)
{
    DWORD conf_in = self->conf_in & ~(ENABLE_PROCESSED_INPUT |
        ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

    DWORD conf_out = self->conf_out | (ENABLE_PROCESSED_OUTPUT |
        ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);

    if (self->mode != PxConsoleMode_Raw) {
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), conf_in);
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), conf_out);

        self->mode = PxConsoleMode_Raw;
    }

    return 1;
}

PxWin32Console* pxWin32ConsoleReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32Console);
}

b32 pxWin32ConsoleCreate(PxWin32Console* self)
{
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &self->conf_in);
    GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &self->conf_out);

    self->mode = PxConsoleMode_Cooked;

    return 1;
}

void pxWin32ConsoleDestroy(PxWin32Console* self)
{
    if (self->mode != PxConsoleMode_Cooked)
        pxWin32ConsoleModeSetCooked(self);

    pxMemorySet(self, sizeof *self, 0xAB);
}

b32 pxWin32ConsoleModeSet(PxWin32Console* self, PxConsoleMode mode)
{
    switch (mode) {
        case PxConsoleMode_Cooked: return pxWin32ConsoleModeSetCooked(self);
        case PxConsoleMode_Raw:    return pxWin32ConsoleModeSetRaw(self);

        default: break;
    }

    return 0;
}

PxConsoleMode pxWin32ConsoleModeGet(PxWin32Console* self)
{
    return self->mode;
}

ssize pxWin32ConsoleWrite(PxWin32Console* self, u8* pntr, ssize start, ssize stop)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    char* memory = ((char*) pntr + start);
    ssize size   = stop - start;
    ssize result = 0;

    while (result < size) {
        DWORD count = 0;

        b32 status = WriteFile(handle, memory + result,
            ((DWORD) size - result), &count, PX_NULL);

        if (status != 0 && count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

ssize pxWin32ConsoleRead(PxWin32Console* self, u8* pntr, ssize start, ssize stop)
{
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);

    char* memory = ((char*) pntr + start);
    ssize size   = stop - start;
    DWORD count  = 0;

    b32 status = ReadFile(handle, memory, size, &count, PX_NULL);

    if (status != 0 && count > 0 && count <= size) return count;

    return 0;
}

b32 pxWin32ConsolePollEvent(PxWin32Console* self, PxConsoleEvent* event)
{
    INPUT_RECORD record;

    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD  count  = 0;

    if (GetNumberOfConsoleInputEvents(handle, &count) == 0 || count <= 0)
        return 0;

    if (ReadConsoleInput(handle, &record, 1, &count) == 0 || count <= 0)
        return 0;

    if (record.EventType == KEY_EVENT) {
        WORD key_code  = record.Event.KeyEvent.wVirtualKeyCode;
        CHAR key_char  = record.Event.KeyEvent.uChar.AsciiChar;

        PxConsoleKeyboardKey key = pxWin32ConsoleConvertKey(key_code, key_char);

        if (record.Event.KeyEvent.bKeyDown != 0) {
            if (event != PX_NULL)
                *event = pxConsoleEventKeyboardKey(key);

            return 1;
        }
    }

    return 0;
}

#endif // PX_CONSOLE_CONSOLE_C
