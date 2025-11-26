#ifndef RN_BASE_MEMORY_COMMON_H
#define RN_BASE_MEMORY_COMMON_H

#include "./import.h"

#define RN_MEMORY_DEFAULT_ALIGNMENT rn_cast(ssize, 16ll)

#define RN_MEMORY_KB rn_cast(ssize, 1000ll)
#define RN_MEMORY_MB rn_cast(ssize, 1000ll * 1000ll)
#define RN_MEMORY_GB rn_cast(ssize, 1000ll * 1000ll * 1000ll)

#define RN_MEMORY_KIB rn_cast(ssize, 1024ll)
#define RN_MEMORY_MIB rn_cast(ssize, 1024ll * 1024ll)
#define RN_MEMORY_GIB rn_cast(ssize, 1024ll * 1024ll * 1024ll)

ssize
rn_memory_align_forward(ssize value, ssize align);

#endif // RN_BASE_MEMORY_COMMON_H
