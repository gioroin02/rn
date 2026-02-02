#ifndef RHO_BASE_MEMORY_COMMON_H
#define RHO_BASE_MEMORY_COMMON_H

#include "import.h"

#define RHO_MEMORY_ALIGNMENT ((RInt) 16)

#define RHO_MEMORY_KB ((RInt) 1000ll)
#define RHO_MEMORY_MB ((RInt) 1000000ll)
#define RHO_MEMORY_GB ((RInt) 1000000000ll)

#define rho_memor_kb(value) (value < 0 || value > RHO_INT_MAX / RHO_MEMORY_KB ? 0 : value * RHO_MEMORY_KB)
#define rho_memory_mb(value) (value < 0 || value > RHO_INT_MAX / RHO_MEMORY_MB ? 0 : value * RHO_MEMORY_MB)
#define rho_memory_gb(value) (value < 0 || value > RHO_INT_MAX / RHO_MEMORY_GB ? 0 : value * RHO_MEMORY_GB)

#define RHO_MEMORY_KIB ((RInt) 0x00000400ll)
#define RHO_MEMORY_MIB ((RInt) 0x00100000ll)
#define RHO_MEMORY_GIB ((RInt) 0x40000000ll)

#define rho_memory_kib(value) (value < 0 || value > RHO_INT_MAX / RHO_MEMORY_KIB ? 0 : value * RHO_MEMORY_KIB)
#define rho_memory_mib(value) (value < 0 || value > RHO_INT_MAX / RHO_MEMORY_MIB ? 0 : value * RHO_MEMORY_MIB)
#define rho_memory_gib(value) (value < 0 || value > RHO_INT_MAX / RHO_MEMORY_GIB ? 0 : value * RHO_MEMORY_GIB)

#define rho_host_byte_order_is_network() (rho_host_byte_order() == RByteOrder_Network ? 1 : 0)
#define rho_host_byte_order_is_reverse() (rho_host_byte_order() == RByteOrder_Reverse ? 1 : 0)

typedef enum RByteOrder
{
    RByteOrder_None,
    RByteOrder_Network,
    RByteOrder_Reverse,
}
RByteOrder;

RByteOrder rho_host_byte_order();

void* rho_memory_set(void* pntr, RInt size, RUint8 value);

void* rho_memory_copy(void* pntr, RInt size, void* value);

void* rho_memory_copy_be(void* pntr, RInt count, RInt size, void* value);

void* rho_memory_copy_le(void* pntr, RInt count, RInt size, void* value);

void* rho_memory_flip(void* pntr, RInt size);

void* rho_memory_align_pntr(void* pntr, RUint align);

RInt rho_memory_align_size(RInt size, RUint align);

#endif
