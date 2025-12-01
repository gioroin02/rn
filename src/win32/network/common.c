#ifndef RN_WIN32_NETWORK_COMMON_C
#define RN_WIN32_NETWORK_COMMON_C

#include "./common.h"

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>

b32
rnWin32NetworkStart()
{
    WSADATA data = {0};

    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        return 0;

    return 1;
}

void
rnWin32NetworkStop()
{
    WSACleanup();
}

#endif // RN_WIN32_NETWORK_COMMON_C
