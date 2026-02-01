#ifndef RHO_SYSTEM_NETWORK_ADDRESS_IP_C
#define RHO_SYSTEM_NETWORK_ADDRESS_IP_C

#include "address-ip.h"

static RBool32 rho_address_ip4_is_equal(RAddressIp4 self, RAddressIp4 value)
{
    for (RInt i = 0; i < RHO_ADDRESS_IP4_SIZE; i += 1) {
        if (self.values[i] != value.values[i])
            return 0;
    }

    return 1;
}

static RBool32 rho_address_ip6_is_equal(RAddressIp6 self, RAddressIp6 value)
{
    for (RInt i = 0; i < RHO_ADDRESS_IP6_SIZE; i += 1) {
        if (self.values[i] != value.values[i])
            return 0;
    }

    return 1;
}

RAddressIp rho_address_ip4_make(RUint8 v0, RUint8 v1, RUint8 v2, RUint8 v3)
{
    RAddressIp result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.kind   = RAddressIp_Ver4;
    result.ip4.v0 = v0;
    result.ip4.v1 = v1;
    result.ip4.v2 = v2;
    result.ip4.v3 = v3;

    return result;
}

RAddressIp rho_address_ip6_make(RUint16 v0, RUint16 v1, RUint16 v2, RUint16 v3, RUint16 v4, RUint16 v5, RUint16 v6, RUint16 v7)
{
    RAddressIp result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.kind   = RAddressIp_Ver6;
    result.ip6.v0 = v0;
    result.ip6.v1 = v1;
    result.ip6.v2 = v2;
    result.ip6.v3 = v3;
    result.ip6.v4 = v4;
    result.ip6.v5 = v5;
    result.ip6.v6 = v6;
    result.ip6.v7 = v7;

    return result;
}

RAddressIp rho_address_ip_none()
{
    RAddressIp result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.kind = RAddressIp_None;

    return result;
}

RAddressIp rho_address_ip_any(RAddressIpKind kind)
{
    RAddressIp result = rho_address_ip_none();

    switch (kind) {
        case RAddressIp_Ver4: return rho_address_ip4_any();
        case RAddressIp_Ver6: return rho_address_ip6_any();

        default: break;
    }

    return result;
}

RAddressIp rho_address_ip_self(RAddressIpKind kind)
{
    RAddressIp result = rho_address_ip_none();

    switch (kind) {
        case RAddressIp_Ver4: return rho_address_ip4_self();
        case RAddressIp_Ver6: return rho_address_ip6_self();

        default: break;
    }

    return result;
}

RBool32 rho_address_ip_is_equal(RAddressIp self, RAddressIp value)
{
    if (self.kind != value.kind) return 0;

    switch (self.kind) {
        case RAddressIp_Ver4:
            return rho_address_ip4_is_equal(self.ip4, value.ip4);

        case RAddressIp_Ver6:
            return rho_address_ip6_is_equal(self.ip6, value.ip6);

        default: break;
    }

    return 0;
}

RHostIp rho_host_ip_make(RAddressIp address, RUint16 port)
{
    RHostIp result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.address = address;
    result.port    = port;

    return result;
}

#endif
