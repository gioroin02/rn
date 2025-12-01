#ifndef RN_WIN32_NETWORK_ADDRESS_C
#define RN_WIN32_NETWORK_ADDRESS_C

#include "./import.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

typedef struct sockaddr_storage RnSockAddrStorage;

typedef struct sockaddr     RnSockAddr;
typedef struct sockaddr_in  RnSockAddrIn4;
typedef struct sockaddr_in6 RnSockAddrIn6;

#define rnSockAddrIn4Address(expr) ((u8*) &((RnSockAddrIn4*) expr)->sin_addr.s_addr)
#define rnSockAddrIn4Port(expr)    ((u8*) &((RnSockAddrIn4*) expr)->sin_port)
#define rnSockAddrIn6Address(expr) ((u8*)  ((RnSockAddrIn6*) expr)->sin6_addr.s6_addr)
#define rnSockAddrIn6Port(expr)    ((u8*) &((RnSockAddrIn6*) expr)->sin6_port)

static u8*
rnCopyNetFromHost(u8* dest, u8* values, ssize size, ssize step)
{
    switch (rnGetHostByteOrder()) {
        case RnByteOrder_Network: {
            for (ssize i = 0; i < size * step; i += 1)
                dest[i] = values[i];
        } break;

        case RnByteOrder_Reverse: {
            for (ssize i = 0; i < size; i += 1) {
                for (ssize j = step; j > 0; j -= 1)
                    dest[i + j - 1] = values[i + j - 1];
            }
        } break;

        default: return 0;
    }

    return dest;
}

static u8*
rnCopyHostFromNet(u8* dest, u8* values, ssize size, ssize step)
{
    switch (rnGetHostByteOrder()) {
        case RnByteOrder_Network: {
            for (ssize i = 0; i < size * step; i += 1)
                dest[i] = values[i];
        } break;

        case RnByteOrder_Reverse: {
            for (ssize i = 0; i < size; i += 1) {
                for (ssize j = step; j > 0; j -= 1)
                    dest[i + j - 1] = values[i + j - 1];
            }
        } break;

        default: return 0;
    }

    return dest;
}

ssize
rnSockAddrStorageSetAddress(RnSockAddrStorage* self, RnAddressIP address)
{
    ssize result = 0;
    u8*   dest   = 0;
    u8*   values = 0;
    ssize size   = 0;
    ssize step   = 0;

    switch (address.kind) {
        case RnAddressIP_IPv4: {
            self->ss_family = AF_INET;

            result = sizeof(RnSockAddrIn4);
            dest   = rnSockAddrIn4Address(self);
            values = address.ipv4.values;
            size   = sizeof(address.ipv4.values);
            step   = sizeof(*(address.ipv4.values));
        } break;

        case RnAddressIP_IPv6: {
            self->ss_family = AF_INET6;

            result = sizeof(RnSockAddrIn6);
            dest   = rnSockAddrIn6Address(self);
            values = address.ipv6.values;
            size   = sizeof(address.ipv6.values);
            step   = sizeof(*(address.ipv6.values));
        } break;

        default: return 0;
    }

    rnCopyNetFromHost(dest, values, size, step);

    return result;
}

ssize
rnSockAddrStorageSetPort(RnSockAddrStorage* self, u16 port)
{
    u8*   dest   = 0;
    u8*   values = ((u8*) &port);
    ssize step   = sizeof(port);

    switch (self->ss_family) {
        case AF_INET:  dest = rnSockAddrIn4Port(self); break;
        case AF_INET6: dest = rnSockAddrIn6Port(self); break;

        default: return 0;
    }

    rnCopyNetFromHost(dest, values, 1, step);

    return step;
}

RnAddressIP
rnSockAddrStorageGetAddress(RnSockAddrStorage* self)
{
    RnAddressIP result = {0};

    u8*   dest   = 0;
    u8*   values = 0;
    ssize size   = 0;
    ssize step   = 0;

    switch (self->ss_family) {
        case AF_INET: {
            result.kind = RnAddressIP_IPv4;

            dest   = result.ipv4.values;
            values = rnSockAddrIn4Address(self);
            size   = sizeof(result.ipv4.values);
            step   = sizeof(*(result.ipv4.values));
        } break;

        case AF_INET6: {
            result.kind = RnAddressIP_IPv4;

            dest   = result.ipv6.values;
            values = rnSockAddrIn6Address(self);
            size   = sizeof(result.ipv6.values);
            step   = sizeof(*(result.ipv6.values));
        } break;

        default: return result;
    }

    rnCopyHostFromNet(dest, values, size, step);

    return result;
}

u16
rnSockAddrStorageGetPort(RnSockAddrStorage* self)
{
    u16 result = 0;

    u8*   dest   = ((u8*) &result);
    u8*   values = 0;
    ssize step   = sizeof(result);

    switch (self->ss_family) {
        case AF_INET:  values = rnSockAddrIn4Port(self); break;
        case AF_INET6: values = rnSockAddrIn6Port(self); break;

        default: return 0;
    }

    rnCopyHostFromNet(dest, values, 1, step);

    return result;
}

RnSockAddrStorage
rnSockAddrStorageMake(RnAddressIP address, u16 port, ssize* size)
{
    RnSockAddrStorage result = {0};

    rnSockAddrStorageSetAddress(&result, address);
    rnSockAddrStorageSetPort(&result, port);

    if (size == 0) return result;

    switch (result.ss_family) {
        case AF_INET:  *size = sizeof(RnSockAddrIn4); break;
        case AF_INET6: *size = sizeof(RnSockAddrIn6); break;

        default: break;
    }

    return result;
}

RnSockAddrStorage
rnSockAddrStorageMakeEmpty(RnAddressIPKind kind)
{
    RnSockAddrStorage result = {0};

    switch (kind) {
        case RnAddressIP_IPv4: result.ss_family = AF_INET;  break;
        case RnAddressIP_IPv6: result.ss_family = AF_INET6; break;

        default: break;
    }

    return result;
}

#endif // RN_WIN32_NETWORK_ADDRESS_C
