#ifndef RN_BASE_MEMORY_COMMON_C
#define RN_BASE_MEMORY_COMMON_C

#include "./common.h"

ssize
rnMemoryAlignForward(ssize value, ssize align)
{
    if (value <= 0 || align <= 1) return 0;

    ssize temp = value % align;

    if (temp != 0)
        return value + align - temp;

    return value;
}

b32
rnMemoryIsByteOrderNetwork()
{
    u16 value = 0xab;

    if (*((u8*) &value) == 0xa)
        return 1;

    return 0;
}

b32
rnMemoryIsByteOrderReverse()
{
    u16 value = 0xab;

    if (*((u8*) &value) == 0xb)
        return 1;

    return 0;
}

#endif // RN_BASE_MEMORY_COMMON_C
