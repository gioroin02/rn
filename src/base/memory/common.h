#ifndef PX_BASE_MEMORY_COMMON_H
#define PX_BASE_MEMORY_COMMON_H

#include "import.h"

#define PX_MEMORY_DEFAULT_ALIGNMENT ((ssize) 16)

#define PX_MEMORY_KB ((ssize) 1000ll)
#define PX_MEMORY_MB ((ssize) 1000ll * 1000ll)
#define PX_MEMORY_GB ((ssize) 1000ll * 1000ll * 1000ll)

#define PX_MEMORY_KIB ((ssize) 1024ll)
#define PX_MEMORY_MIB ((ssize) 1024ll * 1024ll)
#define PX_MEMORY_GIB ((ssize) 1024ll * 1024ll * 1024ll)

#define pxMemoryKB(expr) (((ssize) expr) * PX_MEMORY_KB)
#define pxMemoryMB(expr) (((ssize) expr) * PX_MEMORY_MB)
#define pxMemoryGB(expr) (((ssize) expr) * PX_MEMORY_GB)

#define pxMemoryKiB(expr) (((ssize) expr) * PX_MEMORY_KIB)
#define pxMemoryMiB(expr) (((ssize) expr) * PX_MEMORY_MIB)
#define pxMemoryGiB(expr) (((ssize) expr) * PX_MEMORY_GIB)

#define pxHostByteOrderIsNetwork() \
    (pxGetHostByteOrder() == PxByteOrder_Network ? 1 : 0)

#define pxHostByteOrderIsReverse() \
    (pxGetHostByteOrder() == PxByteOrder_Reverse ? 1 : 0)

typedef enum PxByteOrder
{
    PxByteOrder_None,
    PxByteOrder_Network,
    PxByteOrder_Reverse,
}
PxByteOrder;

void*
pxMemorySet(void* pntr, u8 value, ssize size);

void*
pxMemoryCopy(void* pntr, void* value, ssize size);

void*
pxMemoryCopyOrSet(void* pntr, void* value, ssize size, u8 other);

void*
pxMemoryAlignForward(void* pntr, usize align);

PxByteOrder
pxGetHostByteOrder();

#endif // PX_BASE_MEMORY_COMMON_H
