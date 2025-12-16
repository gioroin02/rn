#ifndef PX_WIN32_NETWORK_COMMON_H
#define PX_WIN32_NETWORK_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

typedef struct sockaddr_storage PxSockAddrStorage;
typedef struct sockaddr         PxSockAddr;
typedef struct sockaddr_in      PxSockAddrIn4;
typedef struct sockaddr_in6     PxSockAddrIn6;

static LPFN_CONNECTEX connectEx = 0;
static LPFN_ACCEPTEX  acceptEx  = 0;

b32
pxWin32NetworkStart();

b32
pxWin32NetworkStartImpl();

void
pxWin32NetworkStop();

void
pxWin32NetworkStopImpl();

#endif // PX_WIN32_NETWORK_COMMON_H
