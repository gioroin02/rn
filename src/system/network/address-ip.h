#ifndef RHO_SYSTEM_NETWORK_ADDRESS_IP_H
#define RHO_SYSTEM_NETWORK_ADDRESS_IP_H

#include "import.h"

#define RHO_ADDRESS_IP4_SIZE ((RInt) 4)
#define RHO_ADDRESS_IP6_SIZE ((RInt) 8)

#define rho_address_ip4_any()  rho_address_ip4_make(0x00, 0x00, 0x00, 0x00)
#define rho_address_ip4_self() rho_address_ip4_make(0x7f, 0x00, 0x00, 0x01)

#define rho_address_ip6_any()  rho_address_ip6_make(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
#define rho_address_ip6_self() rho_address_ip6_make(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01)

typedef enum RAddressIpKind
{
    RAddressIp_None,
    RAddressIp_Ver4,
    RAddressIp_Ver6,
}
RAddressIpKind;

typedef union RAddressIp4
{
    RUint8 values[RHO_ADDRESS_IP4_SIZE];

    struct
    {
        RUint8 v0, v1, v2, v3;
    };
}
RAddressIp4;

typedef union RAddressIp6
{
    RUint16 values[RHO_ADDRESS_IP6_SIZE];

    struct
    {
        RUint16 v0, v1, v2, v3, v4, v5, v6, v7;
    };
}
RAddressIp6;

typedef struct RAddressIp
{
    RAddressIpKind kind;

    union
    {
        RAddressIp4 ip4;
        RAddressIp6 ip6;
    };
}
RAddressIp;

typedef struct RHostIp
{
    RAddressIp address;
    RUint16        port;
}
RHostIp;

RAddressIp rho_address_ip4_make(RUint8 v0, RUint8 v1, RUint8 v2, RUint8 v3);

RAddressIp rho_address_ip6_make(RUint16 v0, RUint16 v1, RUint16 v2, RUint16 v3, RUint16 v4, RUint16 v5, RUint16 v6, RUint16 v7);

RAddressIp rho_address_ip_none();

RAddressIp rho_address_ip_any(RAddressIpKind kind);

RAddressIp rho_address_ip_self(RAddressIpKind kind);

RBool32 rho_address_ip_is_equal(RAddressIp self, RAddressIp value);

RHostIp rho_host_ip_make(RAddressIp address, RUint16 port);

#endif
