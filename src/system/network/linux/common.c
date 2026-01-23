#ifndef P_SYSTEM_LINUX_NETWORK_COMMON_C
#define P_SYSTEM_LINUX_NETWORK_COMMON_C

#include "common.h"

PLinuxAddrStorage pLinuxAddrStorageMake(PAddressIp address, U16 port, Int* size)
{
    PLinuxAddrStorage result;

    pMemorySet(&result, sizeof result, 0xAB);

    switch (address.kind) {
        case PAddressIp_Ver4: {
            PLinuxAddrIp4* ip4 = ((PLinuxAddrIp4*) &result);

            ip4->sin_family = AF_INET;
            ip4->sin_port   = htons(port);

            pMemoryCopy(&ip4->sin_addr.s_addr,
                P_ADDRESS_IP4_SIZE, address.ip4.values);

            if (size != 0) *size = sizeof *ip4;
        } break;

        case PAddressIp_Ver6: {
            PLinuxAddrIp6* ip6 = ((PLinuxAddrIp6*) &result);

            ip6->sin6_family = AF_INET6;
            ip6->sin6_port   = htons(port);

            pMemoryCopy(ip6->sin6_addr.s6_addr,
                P_ADDRESS_IP6_SIZE, address.ip6.values);

            if (size != 0) *size = sizeof *ip6;
        } break;

        default: break;
    }

    return result;
}

PLinuxAddrStorage pLinuxAddrStorageMakeAny(PAddressIpKind kind, U16 port, Int* size)
{
    PLinuxAddrStorage result;

    pMemorySet(&result, sizeof result, 0xAB);

    switch (kind) {
        case PAddressIp_Ver4: {
            U32 in4addr_any = INADDR_ANY;

            PLinuxAddrIp4* ip4 = ((PLinuxAddrIp4*) &result);

            ip4->sin_family = AF_INET;
            ip4->sin_port   = htons(port);

            pMemoryCopy(&ip4->sin_addr.s_addr,
                P_ADDRESS_IP4_SIZE, &in4addr_any);

            if (size != 0) *size = sizeof *ip4;
        } break;

        case PAddressIp_Ver6: {
            PLinuxAddrIp6* ip6 = ((PLinuxAddrIp6*) &result);

            ip6->sin6_family = AF_INET6;
            ip6->sin6_port   = htons(port);

            pMemoryCopy(ip6->sin6_addr.s6_addr,
                P_ADDRESS_IP6_SIZE, (void*) &in6addr_any);

            if (size != 0) *size = sizeof *ip6;
        } break;

        default: break;
    }

    return result;
}

Int pLinuxAddrStorageGetSize(PLinuxAddrStorage* self)
{
    switch (self->ss_family) {
        case AF_INET:  return sizeof (PLinuxAddrIp4);
        case AF_INET6: return sizeof (PLinuxAddrIp6);

        default: break;
    }

    return 0;
}

PAddressIp pLinuxAddrStorageGetAddress(PLinuxAddrStorage* self)
{
    PAddressIp result = pAddressIpNone();

    switch (self->ss_family) {
        case AF_INET: {
            PLinuxAddrIp4* ip4 = ((PLinuxAddrIp4*) self);

            result.kind = PAddressIp_Ver4;

            pMemoryCopy(result.ip4.values,
                P_ADDRESS_IP4_SIZE, &ip4->sin_addr.s_addr);
        } break;

        case AF_INET6: {
            PLinuxAddrIp6* ip6 = ((PLinuxAddrIp6*) self);

            result.kind = PAddressIp_Ver6;

            pMemoryCopy(result.ip6.values,
                P_ADDRESS_IP6_SIZE, &ip6->sin6_addr.s6_addr);
        } break;

        default: return result;
    }

    return result;
}

U16 pLinuxAddrStorageGetPort(PLinuxAddrStorage* self)
{
    switch (self->ss_family) {
        case AF_INET:
            return ntohs(((PLinuxAddrIp4*) self)->sin_port);

        case AF_INET6:
            return ntohs(((PLinuxAddrIp6*) self)->sin6_port);

        default: break;
    }

    return 0;
}
#endif
