#ifndef PX_BASE_STRING_TYPE_C
#define PX_BASE_STRING_TYPE_C

#include "type.h"

PxString8 pxString8Make(u8* values, ssize size)
{
    PxString8 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    if (values == PX_NULL || size < 0)
        return result;

    result.values = values;
    result.size   = size;

    return result;
}

PxString16 pxString16Make(u16* values, ssize size)
{
    PxString16 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    if (values == PX_NULL || size < 0)
        return result;

    result.values = values;
    result.size   = size;

    return result;
}

PxString32 pxString32Make(u32* values, ssize size)
{
    PxString32 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    if (values == PX_NULL || size < 0)
        return result;

    result.values = values;
    result.size   = size;

    return result;
}

#endif // PX_BASE_STRING_TYPE_C
