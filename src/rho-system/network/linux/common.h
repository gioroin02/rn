#ifndef RHO_SYSTEM_NETWORK_LINUX_COMMON_H
#define RHO_SYSTEM_NETWORK_LINUX_COMMON_H

#include "import.h"

#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr_storage RLinuxAddrStorage;
typedef struct sockaddr         RLinuxAddr;
typedef struct sockaddr_in      RLinuxAddrIp4;
typedef struct sockaddr_in6     RLinuxAddrIp6;

RLinuxAddrStorage rho_linux_addr_storage_make(RAddressIp address, RUint16 port, RInt* size);

RLinuxAddrStorage rho_linux_addr_storage_make_any(RAddressIpKind kind, RUint16 port, RInt* size);

RInt rho_linux_addr_storage_size(RLinuxAddrStorage* self);

RAddressIp rho_linux_addr_storage_address(RLinuxAddrStorage* self);

RUint16 rho_linux_addr_storage_port(RLinuxAddrStorage* self);

RHostIp rho_linux_addr_storage_host(RLinuxAddrStorage* self);

#endif
