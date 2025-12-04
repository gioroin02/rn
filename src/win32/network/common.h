#ifndef RN_WIN32_NETWORK_COMMON_H
#define RN_WIN32_NETWORK_COMMON_H

#include "./import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

typedef struct sockaddr_storage RnSockAddrStorage;
typedef struct sockaddr         RnSockAddr;
typedef struct sockaddr_in      RnSockAddrIn4;
typedef struct sockaddr_in6     RnSockAddrIn6;

b32
rnWin32NetworkStart();

void
rnWin32NetworkStop();

#endif // RN_WIN32_NETWORK_COMMON_H
