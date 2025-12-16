#ifndef PX_SYSTEM_NETWORK_ADDRESS_IP_C
#define PX_SYSTEM_NETWORK_ADDRESS_IP_C

#include "address-ip.h"

static b32
pxAddressIPv4IsEqual(PxAddressIPv4 self, PxAddressIPv4 value)
{
    for (ssize i = 0; i < PX_ADDRESS_IPV4_SIZE; i += 1) {
        if (self.values[i] != value.values[i])
            return 0;
    }

    return 1;
}

static b32
pxAddressIPv6IsEqual(PxAddressIPv6 self, PxAddressIPv6 value)
{
    for (ssize i = 0; i < PX_ADDRESS_IPV6_SIZE; i += 1) {
        if (self.values[i] != value.values[i])
            return 0;
    }

    return 1;
}

PxAddressIP
pxAddressIPv4Make(u8 v0, u8 v1, u8 v2, u8 v3)
{
    return (PxAddressIP) {
        .kind = PxAddressIP_IPv4,

        .ipv4.values = {
            [0] = v0, [1] = v1,
            [2] = v2, [3] = v3,
        },
    };
}

PxAddressIP
pxAddressIPv4FromArray(u8* values, ssize size)
{
    PxAddressIP result = {.kind = PxAddressIP_IPv4};

    size = pxClamp(size, 0, PX_ADDRESS_IPV4_SIZE);

    for (ssize i = 0; i < size; i += 1)
        result.ipv4.values[i] = values[i];

    return result;
}

PxAddressIP
pxAddressIPv6Make(u16 v0, u16 v1, u16 v2, u16 v3, u16 v4, u16 v5, u16 v6, u16 v7)
{
    return (PxAddressIP) {
        .kind = PxAddressIP_IPv6,

        .ipv6.values = {
            [0] = v0, [1] = v1, [2] = v2, [3] = v3,
            [4] = v4, [5] = v5, [6] = v6, [7] = v7,
        },
    };
}

PxAddressIP
pxAddressIPv6FromArray(u16* values, ssize size)
{
    PxAddressIP result = {.kind = PxAddressIP_IPv6};

    size = pxClamp(size, 0, PX_ADDRESS_IPV6_SIZE);

    for (ssize i = 0; i < size; i += 1)
        result.ipv6.values[i] = values[i];

    return result;
}

PxAddressIP
pxAddressIPEmpty(PxAddressIPKind kind)
{
    switch (kind) {
        case PxAddressIP_IPv4: return pxAddressIPv4Empty();
        case PxAddressIP_IPv6: return pxAddressIPv6Empty();

        default: break;
    }

    return (PxAddressIP) {0};
}

PxAddressIP
pxAddressIPLocal(PxAddressIPKind kind)
{
    switch (kind) {
        case PxAddressIP_IPv4: return pxAddressIPv4Local();
        case PxAddressIP_IPv6: return pxAddressIPv6Local();

        default: break;
    }

    return (PxAddressIP) {0};
}

b32
pxAddressIPIsEqual(PxAddressIP self, PxAddressIP value)
{
    if (self.kind != value.kind) return 0;

    switch (self.kind) {
        case PxAddressIP_IPv4:
            return pxAddressIPv4IsEqual(self.ipv4, value.ipv4);

        case PxAddressIP_IPv6:
            return pxAddressIPv6IsEqual(self.ipv6, value.ipv6);

        default: break;
    }

    return 0;
}

#endif // PX_SYSTEM_NETWORK_ADDRESS_IP_C
