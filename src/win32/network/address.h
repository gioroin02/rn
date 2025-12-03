#ifndef RN_WIN32_NETWORK_ADDRESS_H
#define RN_WIN32_NETWORK_ADDRESS_H

#include "./import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

typedef struct sockaddr_storage RnSockAddrStorage;
typedef struct sockaddr         RnSockAddr;
typedef struct sockaddr_in      RnSockAddrIn4;
typedef struct sockaddr_in6     RnSockAddrIn6;

RnSockAddrStorage
rnSockAddrStorageMake(RnAddressIP address, u16 port, ssize* size);

RnSockAddrStorage
rnSockAddrStorageMakeAny(RnAddressIPKind kind, u16 port, ssize* size);

RnAddressIP
rnSockAddrStorageGetAddress(RnSockAddrStorage* self);

u16
rnSockAddrStorageGetPort(RnSockAddrStorage* self);

#endif // RN_WIN32_NETWORK_ADDRESS_H
