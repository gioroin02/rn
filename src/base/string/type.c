#ifndef RHO_BASE_STRING_TYPE_C
#define RHO_BASE_STRING_TYPE_C

#include "type.h"

RString8 rho_string8_make(RChar8* values, RInt size)
{
    RString8 result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.values = NULL;
    result.size   = 0;

    if (values != NULL && size > 0) {
        result.values = values;
        result.size   = size;
    }

    return result;
}

RString16 rho_string16_make(RChar16* values, RInt size)
{
    RString16 result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.values = NULL;
    result.size   = 0;

    if (values != NULL && size > 0) {
        result.values = values;
        result.size   = size;
    }

    return result;
}

RString32 rho_string32_make(RChar32* values, RInt size)
{
    RString32 result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.values = NULL;
    result.size   = 0;

    if (values != NULL && size > 0) {
        result.values = values;
        result.size   = size;
    }

    return result;
}

#endif
