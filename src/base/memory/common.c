#ifndef P_BASE_MEMORY_COMMON_C
#define P_BASE_MEMORY_COMMON_C

#include "common.h"

PByteOrder pGetHostByteOrder()
{
    static U16 value = 1;

    U8 bytes[sizeof value] = {0};

    pMemoryCopy(bytes, sizeof value, &value);

    if (bytes[0] == 1)
        return PByteOrder_Reverse;

    return PByteOrder_Network;
}

void* pMemorySet(void* pntr, Int size, U8 value)
{
    if (pntr == NULL) return NULL;

    for (Int i = 0; i < size; i += 1)
        ((U8*) pntr)[i] = value;

    return pntr;
}

void* pMemoryCopy(void* pntr, Int size, void* value)
{
    if (pntr == NULL || value == NULL) return NULL;

    for (Int i = 0; i < size; i += 1)
        ((U8*) pntr)[i] = ((U8*) value)[i];

    return pntr;
}

void* pMemoryCopyOrSet(void* pntr, Int size, void* value, U8 other)
{
    if (pntr == NULL) return NULL;

    if (value == NULL)
        return pMemorySet(pntr, size, other);

    return pMemoryCopy(pntr, size, value);
}

void* pMemoryShiftForw(void* pntr, Int size, Int about, U8 value)
{
    if (pntr == NULL || size < 0 || about < 0 || about >= size)
        return pntr;

    for (Int i = size; i > about; i -= 1)
        ((U8*) pntr)[i - 1] = ((U8*) pntr)[i - about - 1];

    for (Int i = about; i > 0; i -= 1)
        ((U8*) pntr)[i - 1] = value;

    return pntr;
}

void* pMemoryShiftBack(void* pntr, Int size, Int about, U8 value)
{
    if (pntr == NULL || size < 0 || about < 0 || about >= size)
        return pntr;

    for (Int i = 0; i < size - about; i += 1)
        ((U8*) pntr)[i] = ((U8*) pntr)[i + about];

    for (Int i = size - about; i < size; i += 1)
        ((U8*) pntr)[i] = value;

    return pntr;
}

void* pMemoryReverse(void* pntr, Int size)
{
    if (pntr == NULL || size <= 0) return NULL;

    for (Int i = 0, j = size - 1; i < j; i += 1, j -= 1) {
        U8 temp = ((U8*) pntr)[i];

        ((U8*) pntr)[i] = ((U8*) pntr)[j];
        ((U8*) pntr)[j] = temp;
    }

    return pntr;
}

void* pMemoryAlignPntr(void* pntr, Uint align)
{
    if (pntr == NULL || (align & (align - 1)) != 0)
        return NULL;

    Uint dist = ((Uint) pntr) % align;

    if (dist != 0)
        return ((U8*) pntr) + (align - dist);

    return pntr;
}

Int pMemoryAlignSize(Int size, Uint align)
{
    if (size <= 0 || (align & (align - 1)) != 0)
        return 0;

    Uint dist = ((Uint) size) % align;

    if (dist != 0)
        return size + (align - dist);

    return size;
}

#endif
