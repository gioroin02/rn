#ifndef P_SYSTEM_WIN32_WINDOW_EVENT_C
#define P_SYSTEM_WIN32_WINDOW_EVENT_C

#include "event.h"

PWindowKeybdKey pWin32WindowConvertKey(WORD key_code)
{
    switch (key_code) {
        case 'A':            return PWindowKeybd_A;            break;
        case 'B':            return PWindowKeybd_B;            break;
        case 'C':            return PWindowKeybd_C;            break;
        case 'D':            return PWindowKeybd_D;            break;
        case 'E':            return PWindowKeybd_E;            break;
        case 'F':            return PWindowKeybd_F;            break;
        case 'G':            return PWindowKeybd_G;            break;
        case 'H':            return PWindowKeybd_H;            break;
        case 'I':            return PWindowKeybd_I;            break;
        case 'J':            return PWindowKeybd_J;            break;
        case 'K':            return PWindowKeybd_K;            break;
        case 'L':            return PWindowKeybd_L;            break;
        case 'M':            return PWindowKeybd_M;            break;
        case 'N':            return PWindowKeybd_N;            break;
        case 'O':            return PWindowKeybd_O;            break;
        case 'P':            return PWindowKeybd_P;            break;
        case 'Q':            return PWindowKeybd_Q;            break;
        case 'R':            return PWindowKeybd_R;            break;
        case 'S':            return PWindowKeybd_S;            break;
        case 'T':            return PWindowKeybd_T;            break;
        case 'U':            return PWindowKeybd_U;            break;
        case 'V':            return PWindowKeybd_V;            break;
        case 'W':            return PWindowKeybd_W;            break;
        case 'X':            return PWindowKeybd_X;            break;
        case 'Y':            return PWindowKeybd_Y;            break;
        case 'Z':            return PWindowKeybd_Z;            break;
        case '0':            return PWindowKeybd_0;            break;
        case '1':            return PWindowKeybd_1;            break;
        case '2':            return PWindowKeybd_2;            break;
        case '3':            return PWindowKeybd_3;            break;
        case '4':            return PWindowKeybd_4;            break;
        case '5':            return PWindowKeybd_5;            break;
        case '6':            return PWindowKeybd_6;            break;
        case '7':            return PWindowKeybd_7;            break;
        case '8':            return PWindowKeybd_8;            break;
        case '9':            return PWindowKeybd_9;            break;
        case VK_SPACE:       return PWindowKeybd_Space;        break;
        case VK_OEM_MINUS:   return PWindowKeybd_Minus;        break;
        case VK_OEM_PLUS:    return PWindowKeybd_Equal;        break;
        case VK_OEM_4:       return PWindowKeybd_SquareLeft;   break;
        case VK_OEM_6:       return PWindowKeybd_SquareRight;  break;
        case VK_OEM_5:       return PWindowKeybd_BackSlash;    break;
        case VK_OEM_1:       return PWindowKeybd_SemiColon;    break;
        case VK_OEM_7:       return PWindowKeybd_Apostrophe;   break;
        case VK_OEM_3:       return PWindowKeybd_Grave;        break;
        case VK_OEM_COMMA:   return PWindowKeybd_Comma;        break;
        case VK_OEM_PERIOD:  return PWindowKeybd_Period;       break;
        case VK_OEM_2:       return PWindowKeybd_Slash;        break;
        case VK_UP:          return PWindowKeybd_Up;           break;
        case VK_DOWN:        return PWindowKeybd_Down;         break;
        case VK_LEFT:        return PWindowKeybd_Left;         break;
        case VK_RIGHT:       return PWindowKeybd_Right;        break;
        case VK_HOME:        return PWindowKeybd_Home;         break;
        case VK_END:         return PWindowKeybd_End;          break;
        case VK_PRIOR:       return PWindowKeybd_PageUp;       break;
        case VK_NEXT:        return PWindowKeybd_PageDown;     break;
        case VK_INSERT:      return PWindowKeybd_Insert;       break;
        case VK_DELETE:      return PWindowKeybd_Delete;       break;
        case VK_F1:          return PWindowKeybd_F1;           break;
        case VK_F2:          return PWindowKeybd_F2;           break;
        case VK_F3:          return PWindowKeybd_F3;           break;
        case VK_F4:          return PWindowKeybd_F4;           break;
        case VK_F5:          return PWindowKeybd_F5;           break;
        case VK_F6:          return PWindowKeybd_F6;           break;
        case VK_F7:          return PWindowKeybd_F7;           break;
        case VK_F8:          return PWindowKeybd_F8;           break;
        case VK_F9:          return PWindowKeybd_F9;           break;
        case VK_F10:         return PWindowKeybd_F10;          break;
        case VK_F11:         return PWindowKeybd_F11;          break;
        case VK_F12:         return PWindowKeybd_F12;          break;
        case VK_RETURN:      return PWindowKeybd_Enter;        break;
        case VK_ESCAPE:      return PWindowKeybd_Escape;       break;
        case VK_BACK:        return PWindowKeybd_BackSpace;    break;
        case VK_TAB:         return PWindowKeybd_Tab;          break;

        default: break;
    }

    return PWindowKeybd_None;
}

#endif // P_SYSTEM_WIN32_WINDOW_EVENT_C
