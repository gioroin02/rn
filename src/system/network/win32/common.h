#ifndef RHO_SYSTEM_NETWORK_WIN32_COMMON_H
#define RHO_SYSTEM_NETWORK_WIN32_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

typedef struct sockaddr_storage RWin32AddrStorage;
typedef struct sockaddr         RWin32Addr;
typedef struct sockaddr_in      RWin32AddrIp4;
typedef struct sockaddr_in6     RWin32AddrIp6;

extern LPFN_CONNECTEX WSAConnectEx;
extern LPFN_ACCEPTEX  WSAAcceptEx;

RBool32 rho_win32_network_start();

void rho_win32_network_stop();

RWin32AddrStorage rho_win32_addr_storage_make(RAddressIp address, RUint16 port, RInt* size);

RWin32AddrStorage rho_win32_addr_storage_make_any(RAddressIpKind kind, RUint16 port, RInt* size);

RInt rho_win32_addr_storage_size(RWin32AddrStorage* self);

RAddressIp rho_win32_addr_storage_address(RWin32AddrStorage* self);

RUint16 rho_win32_addr_storage_port(RWin32AddrStorage* self);

PHostIp rho_win32_addr_storage_host(RWin32AddrStorage* self);

#endif
