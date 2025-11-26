#ifndef RN_BASE_MEMORY_COMMON_C
#define RN_BASE_MEMORY_COMMON_C

#include "./common.h"

ssize
rn_memory_align_forward(ssize value, ssize align)
{
    if (value <= 0 || align <= 1) return 0;

    ssize temp = value % align;

    if (temp != 0)
        return value + align - temp;

    return value;
}

#endif // RN_BASE_MEMORY_COMMON_C
