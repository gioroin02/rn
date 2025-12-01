#ifndef RN_SYSTEM_NETWORK_COMMON_C
#define RN_SYSTEM_NETWORK_COMMON_C

#include "./common.h"

#if RN_SYSTEM == RN_SYSTEM_WINDOWS

    #include "../../win32/network/common.c"

    #define __rnSystemNetworkStart__ rnWin32NetworkStart
    #define __rnSystemNetworkStop__  rnWin32NetworkStop

#elif RN_SYSTEM == RN_SYSTEM_LINUX

    #define __rnSystemNetworkStart__ b32  rnLinuxNetworkStart() { return 1; }
    #define __rnSystemNetworkStop__  void rnLinuxNetworkStop()  {}

#else

    #error "Unknown platform"

#endif

b32
rnSystemNetworkStart()
{
    return __rnSystemNetworkStart__();
}

void
rnSystemNetworkStop()
{
    __rnSystemNetworkStop__();
}

#endif // RN_SYSTEM_NETWORK_COMMON_C
