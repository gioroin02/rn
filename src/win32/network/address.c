#ifndef PX_WIN32_NETWORK_ADDRESS_C
#define PX_WIN32_NETWORK_ADDRESS_C

#include "address.h"

PxSockAddrStorage
pxSockAddrStorageMake(PxAddressIP address, u16 port, ssize* size)
{
    PxSockAddrStorage result = {0};

    switch (address.kind) {
        case PxAddressIP_IPv4: {
            PxSockAddrIn4* ipv4 = ((PxSockAddrIn4*) &result);

            ipv4->sin_family = AF_INET;
            ipv4->sin_port   = htons(port);

            for (ssize i = 0; i < PX_ADDRESS_IPV4_SIZE; i += 1)
                ((u8*) &ipv4->sin_addr.s_addr)[i] = ((u8*) address.ipv4.values)[i];

            if (size != 0) *size = sizeof(PxSockAddrIn4);
        } break;

        case PxAddressIP_IPv6: {
            PxSockAddrIn6* ipv6 = ((PxSockAddrIn6*) &result);

            ipv6->sin6_family = AF_INET6;
            ipv6->sin6_port   = htons(port);

            for (ssize i = 0; i < PX_ADDRESS_IPV6_SIZE; i += 1)
                ((u16*) &ipv6->sin6_addr.s6_addr)[i] = ((u16*) address.ipv6.values)[i];

            if (size != 0) *size = sizeof(PxSockAddrIn6);
        } break;

        default: break;
    }

    return result;
}

PxSockAddrStorage
pxSockAddrStorageMakeAny(PxAddressIPKind kind, u16 port, ssize* size)
{
    PxSockAddrStorage result = {0};

    switch (kind) {
        case PxAddressIP_IPv4: {
            u32 in4addr_any = INADDR_ANY;

            PxSockAddrIn4* ipv4 = ((PxSockAddrIn4*) &result);

            ipv4->sin_family = AF_INET;
            ipv4->sin_port   = htons(port);

            for (ssize i = 0; i < PX_ADDRESS_IPV4_SIZE; i += 1)
                ((u8*) &ipv4->sin_addr.s_addr)[i] = ((u8*) &in4addr_any)[i];

            if (size != 0) *size = sizeof(PxSockAddrIn4);
        } break;

        case PxAddressIP_IPv6: {
            PxSockAddrIn6* ipv6 = ((PxSockAddrIn6*) &result);

            ipv6->sin6_family = AF_INET6;
            ipv6->sin6_port   = htons(port);

            for (ssize i = 0; i < PX_ADDRESS_IPV6_SIZE; i += 1)
                ((u16*) &ipv6->sin6_addr.s6_addr)[i] = ((u16*) &in6addr_any)[i];

            if (size != 0) *size = sizeof(PxSockAddrIn6);
        } break;

        default: break;
    }

    return result;
}

PxAddressIP
pxSockAddrStorageGetAddress(PxSockAddrStorage* self)
{
    PxAddressIP result = {0};

    switch (self->ss_family) {
        case AF_INET: {
            result.kind = PxAddressIP_IPv4;

            PxSockAddrIn4* ipv4 = ((PxSockAddrIn4*) self);

            for (ssize i = 0; i < PX_ADDRESS_IPV4_SIZE; i += 1)
                ((u8*) result.ipv4.values)[i] = ((u8*) &ipv4->sin_addr.s_addr)[i];
        } break;

        case AF_INET6: {
            result.kind = PxAddressIP_IPv6;

            PxSockAddrIn6* ipv6 = ((PxSockAddrIn6*) self);

            for (ssize i = 0; i < PX_ADDRESS_IPV6_SIZE; i += 1)
                ((u16*) result.ipv6.values)[i] = ((u16*) &ipv6->sin6_addr.s6_addr)[i];
        } break;

        default: return result;
    }

    return result;
}

u16
pxSockAddrStorageGetPort(PxSockAddrStorage* self)
{
    switch (self->ss_family) {
        case AF_INET:
            return ntohs(((PxSockAddrIn4*) self)->sin_port);

        case AF_INET6:
            return ntohs(((PxSockAddrIn6*) self)->sin6_port);

        default: break;
    }

    return 0;
}

#endif // PX_WIN32_NETWORK_ADDRESS_C
