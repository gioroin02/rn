#ifndef RHO_SYSTEM_NETWORK_LINUX_COMMON_C
#define RHO_SYSTEM_NETWORK_LINUX_COMMON_C

#include "common.h"

RLinuxAddrStorage rho_linux_addr_storage_make(RAddressIp address, RUint16 port, RInt* size)
{
    RLinuxAddrStorage result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    switch (address.kind) {
        case RAddressIp_Ver4: {
            RLinuxAddrIp4* ip4 = (RLinuxAddrIp4*) &result;

            ip4->sin_family = AF_INET;
            ip4->sin_port   = htons(port);

            rho_memory_copy(&ip4->sin_addr.s_addr,
                RHO_ADDRESS_IP4_SIZE, address.ip4.values);

            if (size != 0) *size = sizeof *ip4;
        } break;

        case RAddressIp_Ver6: {
            RLinuxAddrIp6* ip6 = (RLinuxAddrIp6*) &result;

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

RLinuxAddrStorage rho_linux_addr_storage_make_any(RAddressIpKind kind, RUint16 port, RInt* size)
{
    RLinuxAddrStorage result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    switch (kind) {
        case RAddressIp_Ver4: {
            RUint32 in4addr_any = INADDR_ANY;

            RLinuxAddrIp4* ip4 = (RLinuxAddrIp4*) &result;

            ip4->sin_family = AF_INET;
            ip4->sin_port   = htons(port);

            rho_memory_copy(&ip4->sin_addr.s_addr,
                RHO_ADDRESS_IP4_SIZE, &in4addr_any);

            if (size != 0) *size = sizeof *ip4;
        } break;

        case RAddressIp_Ver6: {
            RLinuxAddrIp6* ip6 = (RLinuxAddrIp6*) &result;

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

RInt rho_linux_addr_storage_size(RLinuxAddrStorage* self)
{
    switch (self->ss_family) {
        case AF_INET:  return sizeof (RLinuxAddrIp4);
        case AF_INET6: return sizeof (RLinuxAddrIp6);

        default: break;
    }

    return 0;
}

RAddressIp rho_linux_addr_storage_address(RLinuxAddrStorage* self)
{
    RAddressIp result = rho_address_ip_none();

    switch (self->ss_family) {
        case AF_INET: {
            RLinuxAddrIp4* ip4 = (RLinuxAddrIp4*) self;

            result.kind = RAddressIp_Ver4;

            rho_memory_copy(result.ip4.values,
                RHO_ADDRESS_IP4_SIZE, &ip4->sin_addr.s_addr);
        } break;

        case AF_INET6: {
            RLinuxAddrIp6* ip6 = (RLinuxAddrIp6*) self;

            result.kind = RAddressIp_Ver6;

            rho_memory_copy(result.ip6.values,
                RHO_ADDRESS_IP6_SIZE, &ip6->sin6_addr.s6_addr);
        } break;

        default: return result;
    }

    return result;
}

RUint16 rho_linux_addr_storage_port(RLinuxAddrStorage* self)
{
    switch (self->ss_family) {
        case AF_INET:
            return ntohs(((RLinuxAddrIp4*) self)->sin_port);

        case AF_INET6:
            return ntohs(((RLinuxAddrIp6*) self)->sin6_port);

        default: break;
    }

    return 0;
}

RHostIp rho_linux_addr_storage_host(RLinuxAddrStorage* self)
{
    RAddressIp address = rho_linux_addr_storage_address(self);
    RUint16    port    = rho_linux_addr_storage_port(self);

    return rho_host_ip_make(address, port);
}

#endif
