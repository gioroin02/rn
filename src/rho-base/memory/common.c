#ifndef RHO_BASE_MEMORY_COMMON_C
#define RHO_BASE_MEMORY_COMMON_C

#include "common.h"

RByteOrder rho_host_byte_order()
{
    static RUint16 value = 1;

    RUint8 bytes[sizeof value] = {0};

    rho_memory_copy(bytes, sizeof value, &value);

    if (bytes[0] == 1)
        return RByteOrder_Reverse;

    return RByteOrder_Network;
}

void* rho_memory_set(void* pntr, RInt size, RUint8 value)
{
    if (pntr == NULL) return NULL;

    for (RInt i = 0; i < size; i += 1)
        ((RUint8*) pntr)[i] = value;

    return pntr;
}

void* rho_memory_copy(void* pntr, RInt size, void* value)
{
    if (pntr == NULL || value == NULL) return NULL;

    for (RInt i = 0; i < size; i += 1)
        ((RUint8*) pntr)[i] = ((RUint8*) value)[i];

    return pntr;
}

void* rho_memory_copy_be(void* pntr, RInt count, RInt size, void* value)
{
    if (pntr == NULL || value == NULL) return NULL;

    if (count < 0 || size <= 0 || count > RHO_INT_MAX / size)
        return NULL;

    switch (rho_host_byte_order()) {
        case RByteOrder_Network: {
            for (RInt i = 0; i < count * size; i += 1)
                ((RUint8*) pntr)[i] = ((RUint8*) value)[i];
        } break;

        case RByteOrder_Reverse: {
            for (RInt i = 0; i < count; i += 1) {
                for (RInt j = 0; j < size; j += 1) {
                    RInt k0 = i * size + j;
                    RInt k1 = i * size + size - j - 1;

                    ((RUint8*) pntr)[k0] = ((RUint8*) value)[k1];
                }
            }
        } break;

        default: return NULL;
    }

    return pntr;
}

void* rho_memory_copy_le(void* pntr, RInt count, RInt size, void* value)
{
    if (pntr == NULL || value == NULL) return NULL;

    if (count < 0 || size <= 0 || count > RHO_INT_MAX / size)
        return NULL;

    switch (rho_host_byte_order()) {
        case RByteOrder_Reverse: {
            for (RInt i = 0; i < count * size; i += 1)
                ((RUint8*) pntr)[i] = ((RUint8*) value)[i];
        } break;

        case RByteOrder_Network: {
            for (RInt i = 0; i < count; i += 1) {
                for (RInt j = 0; j < size; j += 1) {
                    RInt k0 = i * size + j;
                    RInt k1 = i * size + size - j - 1;

                    ((RUint8*) pntr)[k0] = ((RUint8*) value)[k1];
                }
            }
        } break;


        default: return NULL;
    }

    return pntr;
}

void* rho_memory_flip(void* pntr, RInt size)
{
    if (pntr == NULL || size <= 0) return NULL;

    for (RInt i = 0, j = size - 1; i < j; i += 1, j -= 1) {
        RUint8 temp = ((RUint8*) pntr)[i];

        ((RUint8*) pntr)[i] = ((RUint8*) pntr)[j];
        ((RUint8*) pntr)[j] = temp;
    }

    return pntr;
}

void* rho_memory_align_pntr(void* pntr, RUint align)
{
    if (pntr == NULL || (align & (align - 1)) != 0)
        return NULL;

    RUint dist = ((RUint) pntr) % align;

    if (dist != 0)
        return ((RUint8*) pntr) + (align - dist);

    return pntr;
}

RInt rho_memory_align_size(RInt size, RUint align)
{
    if (size <= 0 || (align & (align - 1)) != 0)
        return 0;

    RUint dist = ((RUint) size) % align;

    if (dist != 0)
        return size + (align - dist);

    return size;
}

#endif
