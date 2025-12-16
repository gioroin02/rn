#ifndef PX_BASE_MEMORY_COMMON_C
#define PX_BASE_MEMORY_COMMON_C

#include "common.h"

void*
pxMemorySet(void* pntr, u8 value, ssize size)
{
    ssize index = 0;

    if (pntr == PX_NULL) return PX_NULL;

    for (index = 0; index < size; index += 1)
        ((u8*) pntr)[index] = value;

    return pntr;
}

void*
pxMemoryCopy(void* pntr, void* value, ssize size)
{
    ssize index = 0;

    if (pntr == PX_NULL || value == PX_NULL) return PX_NULL;

    for (index = 0; index < size; index += 1)
        ((u8*) pntr)[index] = ((u8*) value)[index];

    return pntr;
}

void*
pxMemoryCopyOrSet(void* pntr, void* value, ssize size, u8 other)
{
    if (pntr == PX_NULL) return PX_NULL;

    if (value == PX_NULL)
        return pxMemorySet(pntr, other, size);

    return pxMemoryCopy(pntr, value, size);
}

void*
pxMemoryAlignForward(void* pntr, usize align)
{
    usize dist = ((usize) pntr) % align;

    if (pntr == PX_NULL) return PX_NULL;

    if (dist != 0)
        return ((u8*) pntr) + align - dist;

    return pntr;
}

PxByteOrder
pxGetHostByteOrder()
{
    u32 value               = 1;
    u8  bytes[sizeof value] = {0};

    pxMemoryCopy(bytes, &value, sizeof *bytes);

    if (bytes[0] == 1)
        return PxByteOrder_Reverse;

    return PxByteOrder_Network;
}

#endif // PX_BASE_MEMORY_COMMON_C
