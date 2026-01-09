#ifndef PX_BASE_STRING_TYPE_H
#define PX_BASE_STRING_TYPE_H

#include "import.h"

#define pxString8(arr)  pxString8Make(((u8*) arr),   sizeof (arr) / sizeof *(arr))
#define pxString16(arr) pxString16Make(((u16*) arr), sizeof (arr) / sizeof *(arr))
#define pxString32(arr) pxString32Make(((u32*) arr), sizeof (arr) / sizeof *(arr))

typedef struct PxString8
{
    u8*   values;
    ssize size;
}
PxString8;

typedef struct PxString16
{
    u16*  values;
    ssize size;
}
PxString16;

typedef struct PxString32
{
    u32*  values;
    ssize size;
}
PxString32;

PxString8 pxString8Make(u8* values, ssize size);

PxString16 pxString16Make(u16* values, ssize size);

PxString32 pxString32Make(u32* values, ssize size);

#endif // PX_BASE_STRING_TYPE_H
