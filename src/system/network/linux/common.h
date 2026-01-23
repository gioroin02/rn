#ifndef P_SYSTEM_LINUX_NETWORK_COMMON_H
#define P_SYSTEM_LINUX_NETWORK_COMMON_H

#include "import.h"

#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr_storage PLinuxAddrStorage;
typedef struct sockaddr         PLinuxAddr;
typedef struct sockaddr_in      PLinuxAddrIp4;
typedef struct sockaddr_in6     PLinuxAddrIp6;

PLinuxAddrStorage pLinuxAddrStorageMake(PAddressIp address, U16 port, Int* size);

PLinuxAddrStorage pLinuxAddrStorageMakeAny(PAddressIpKind kind, U16 port, Int* size);

Int pLinuxAddrStorageGetSize(PLinuxAddrStorage* self);

PAddressIp pLinuxAddrStorageGetAddress(PLinuxAddrStorage* self);

U16 pLinuxAddrStorageGetPort(PLinuxAddrStorage* self);

#endif
