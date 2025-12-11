#ifndef RN_BASE_STRING_STRING_H
#define RN_BASE_STRING_STRING_H

#include "./import.h"

#define rnStr8(memory) \
    ((RnString8) {.values = ((u8*) memory), .size = sizeof(memory) / sizeof(memory[0]) - 1})

#define rnStr16(memory) \
    ((RnString16) {.values = ((u16*) memory), .size = sizeof(memory) / sizeof(memory[0]) - 1})

#define rnStr32(memory) \
    ((RnString32) {.values = ((u32*) memory), .size = sizeof(memory) / sizeof(memory[0]) - 1})

typedef struct RnString8
{
    u8*   values;
    ssize size;
}
RnString8;

typedef struct RnString16
{
    u16*  values;
    ssize size;
}
RnString16;

typedef struct RnString32
{
    u8*   values;
    ssize size;
}
RnString32;

#endif // RN_BASE_STRING_STRING_H
