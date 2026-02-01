#ifndef RHO_SYSTEM_NETWORK_WIN32_COMMON_C
#define RHO_SYSTEM_NETWORK_WIN32_COMMON_C

#include "common.h"

static volatile LONG rho_win32_winsock_count = 0;

LPFN_CONNECTEX WSAConnectEx = (LPFN_CONNECTEX) NULL;
LPFN_ACCEPTEX  WSAAcceptEx  = (LPFN_ACCEPTEX)  NULL;

static RBool32 __rho_win32_network_start__()
{
    WSADATA data;

    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) return 0;

    SOCKET handle = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);

    if (handle == INVALID_SOCKET) return 0;

    DWORD bytes = 0;
    GUID  guid0 = WSAID_CONNECTEX;
    GUID  guid1 = WSAID_ACCEPTEX;

    WSAIoctl(handle, SIO_GET_EXTENSION_FUNCTION_POINTER,
        &guid0, sizeof guid0, &WSAConnectEx, sizeof WSAConnectEx, &bytes, 0, 0);

    WSAIoctl(handle, SIO_GET_EXTENSION_FUNCTION_POINTER,
        &guid1, sizeof guid1, &WSAAcceptEx, sizeof WSAAcceptEx, &bytes, 0, 0);

    closesocket(handle);

    if (WSAConnectEx != NULL && WSAAcceptEx != NULL) return 1;

    rho_win32_network_stop();

    return 0;
}

static void __rho_win32_network_stop__()
{
    WSAConnectEx = NULL;
    WSAAcceptEx  = NULL;

    WSACleanup();
}

RBool32 rho_win32_network_start()
{
    if (InterlockedIncrement(&rho_win32_winsock_count) == 1)
        return __rho_win32_network_start__();

    return 1;
}

void rho_win32_network_stop()
{
    if (InterlockedDecrement(&rho_win32_winsock_count) == 0)
        __rho_win32_network_stop__();
}

RWin32AddrStorage rho_win32_addr_storage_make(RAddressIp address, RUint16 port, RInt* size)
{
    RWin32AddrStorage result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    switch (address.kind) {
        case RAddressIp_Ver4: {
            RWin32AddrIp4* ip4 = (RWin32AddrIp4*) &result;

            ip4->sin_family = AF_INET;
            ip4->sin_port   = htons(port);

            rho_memory_copy(&ip4->sin_addr.s_addr,
                RHO_ADDRESS_IP4_SIZE, address.ip4.values);

            if (size != 0) *size = sizeof *ip4;
        } break;

        case RAddressIp_Ver6: {
            RWin32AddrIp6* ip6 = (RWin32AddrIp6*) &result;

            ip6->sin6_family = AF_INET6;
            ip6->sin6_port   = htons(port);

            rho_memory_copy(ip6->sin6_addr.s6_addr,
                RHO_ADDRESS_IP6_SIZE, address.ip6.values);

            if (size != 0) *size = sizeof *ip6;
        } break;

        default: break;
    }

    return result;
}

RWin32AddrStorage rho_win32_addr_storage_make_any(RAddressIpKind kind, RUint16 port, RInt* size)
{
    RWin32AddrStorage result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    switch (kind) {
        case RAddressIp_Ver4: {
            RUint32 in4addr_any = INADDR_ANY;

            RWin32AddrIp4* ip4 = (RWin32AddrIp4*) &result;

            ip4->sin_family = AF_INET;
            ip4->sin_port   = htons(port);

            rho_memory_copy(&ip4->sin_addr.s_addr,
                RHO_ADDRESS_IP4_SIZE, &in4addr_any);

            if (size != 0) *size = sizeof *ip4;
        } break;

        case RAddressIp_Ver6: {
            RWin32AddrIp6* ip6 = (RWin32AddrIp6*) &result;

            ip6->sin6_family = AF_INET6;
            ip6->sin6_port   = htons(port);

            rho_memory_copy(ip6->sin6_addr.s6_addr,
                RHO_ADDRESS_IP6_SIZE, (void*) &in6addr_any);

            if (size != 0) *size = sizeof *ip6;
        } break;

        default: break;
    }

    return result;
}

RInt rho_win32_addr_storage_size(RWin32AddrStorage* self)
{
    switch (self->ss_family) {
        case AF_INET:  return sizeof (RWin32AddrIp4);
        case AF_INET6: return sizeof (RWin32AddrIp6);

        default: break;
    }

    return 0;
}

RAddressIp rho_win32_addr_storage_address(RWin32AddrStorage* self)
{
    RAddressIp result = rAddressIpNone();

    switch (self->ss_family) {
        case AF_INET: {
            RWin32AddrIp4* ip4 = (RWin32AddrIp4*) self;

            result.kind = RAddressIp_Ver4;

            rho_memory_copy(result.ip4.values,
                RHO_ADDRESS_IP4_SIZE, &ip4->sin_addr.s_addr);
        } break;

        case AF_INET6: {
            RWin32AddrIp6* ip6 = (RWin32AddrIp6*) self;

            result.kind = RAddressIp_Ver6;

            rho_memory_copy(result.ip6.values,
                RHO_ADDRESS_IP6_SIZE, &ip6->sin6_addr.s6_addr);
        } break;

        default: return result;
    }

    return result;
}

RUint16 rho_win32_addr_storage_port(RWin32AddrStorage* self)
{
    switch (self->ss_family) {
        case AF_INET:
            return ntohs(((RWin32AddrIp4*) self)->sin_port);

        case AF_INET6:
            return ntohs(((RWin32AddrIp6*) self)->sin6_port);

        default: break;
    }

    return 0;
}

RHostIp rho_win32_addr_storage_host(RWin32AddrStorage* self)
{
    RAddressIp address = rho_win32_addr_storage_address(self);
    RUint16    port    = rho_win32_addr_storage_port(self);

    return rho_host_ip_make(address, port);
}

#endif
