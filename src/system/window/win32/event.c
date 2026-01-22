#ifndef P_SYSTEM_WIN32_WINDOW_EVENT_C
#define P_SYSTEM_WIN32_WINDOW_EVENT_C

#include "event.h"

PWindowKeyboardKey pWin32WindowConvertKey(WORD key_code)
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

#endif // P_SYSTEM_WIN32_WINDOW_EVENT_C
