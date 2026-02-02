#ifndef RHO_BASE_STRING_TYPE_H
#define RHO_BASE_STRING_TYPE_H

#include "import.h"

#define rho_string8(arr)  rho_string8_make((RChar8*) (arr),   sizeof (arr) / sizeof *(arr) - 1)
#define rho_string16(arr) rho_string16_make((RChar16*) (arr), sizeof (arr) / sizeof *(arr) - 1)
#define rho_string32(arr) rho_string32_make((RChar32*) (arr), sizeof (arr) / sizeof *(arr) - 1)

typedef struct RString8
{
    RChar8* values;
    RInt    size;
}
RString8;

typedef struct RString16
{
    RChar16* values;
    RInt     size;
}
RString16;

typedef struct RString32
{
    RChar32* values;
    RInt     size;
}
RString32;

RString8 rho_string8_make(RChar8* values, RInt size);

RString16 rho_string16_make(RChar16* values, RInt size);

RString32 rho_string32_make(RChar32* values, RInt size);

#endif
