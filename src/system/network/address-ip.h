#ifndef PX_SYSTEM_NETWORK_ADDRESS_IP_H
#define PX_SYSTEM_NETWORK_ADDRESS_IP_H

#include "import.h"

#define PX_ADDRESS_IPV4_SIZE ((ssize) 4)

#define pxAddressIPv4Empty() \
    ((PxAddressIP) {.kind = PxAddressIP_IPv4, .ipv4.values = {0}})

#define pxAddressIPv4Local() \
    ((PxAddressIP) {.kind = PxAddressIP_IPv4, .ipv4.values = {[0] = 127, [3] = 1}})

#define PX_ADDRESS_IPV6_SIZE ((ssize) 8)

#define pxAddressIPv6Empty() \
    ((PxAddressIP) {.kind = PxAddressIP_IPv6, .ipv6.values = {0}})

#define pxAddressIPv6Local() \
    ((PxAddressIP) {.kind = PxAddressIP_IPv6, .ipv6.values = {[7] = 1}})

typedef enum PxAddressIPKind
{
    PxAddressIP_None,
    PxAddressIP_IPv4,
    PxAddressIP_IPv6,
}
PxAddressIPKind;

typedef union PxAddressIPv4
{
    u8 values[PX_ADDRESS_IPV4_SIZE];

    struct
    {
        u8 v0, v1;
        u8 v2, v3;
    };
}
PxAddressIPv4;

typedef union PxAddressIPv6
{
    u8 values[PX_ADDRESS_IPV6_SIZE];

    struct
    {
        u16 v0, v1, v2, v3;
        u16 v4, v5, v6, v7;
    };
}
PxAddressIPv6;

typedef struct PxAddressIP
{
    PxAddressIPKind kind;

    union
    {
        PxAddressIPv4 ipv4;
        PxAddressIPv6 ipv6;
    };
}
PxAddressIP;

PxAddressIP
pxAddressIPv4Make(u8 v0, u8 v1, u8 v2, u8 v3);

PxAddressIP
pxAddressIPv4FromArray(u8* values, ssize size);

PxAddressIP
pxAddressIPv6Make(u16 v0, u16 v1, u16 v2, u16 v3, u16 v4, u16 v5, u16 v6, u16 v7);

PxAddressIP
pxAddressIPv6FromArray(u16* values, ssize size);

PxAddressIP
pxAddressIPEmpty(PxAddressIPKind kind);

PxAddressIP
pxAddressIPLocal(PxAddressIPKind kind);

b32
pxAddressIPIsEqual(PxAddressIP self, PxAddressIP value);

#endif // PX_SYSTEM_NETWORK_ADDRESS_IP_H
