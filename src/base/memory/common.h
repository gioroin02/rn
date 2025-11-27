#ifndef RN_BASE_MEMORY_COMMON_H
#define RN_BASE_MEMORY_COMMON_H

#include "./import.h"

#define RN_MEMORY_DEFAULT_ALIGNMENT ((ssize) 16ll)

#define RN_MEMORY_KB ((ssize) 1000ll)
#define RN_MEMORY_MB ((ssize) 1000ll * 1000ll)
#define RN_MEMORY_GB ((ssize) 1000ll * 1000ll * 1000ll)

#define RN_MEMORY_KIB ((ssize) 1024ll)
#define RN_MEMORY_MIB ((ssize) 1024ll * 1024ll)
#define RN_MEMORY_GIB ((ssize) 1024ll * 1024ll * 1024ll)

ssize
rnMemoryAlignForward(ssize value, ssize align);

#endif // RN_BASE_MEMORY_COMMON_H
