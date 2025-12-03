#ifndef RN_SYSTEM_NETWORK_SOCKET_UDP_C
#define RN_SYSTEM_NETWORK_SOCKET_UDP_C

#include "./socket-udp.h"

#if RN_SYSTEM == RN_SYSTEM_WINDOWS

    #include "../../win32/network/export.c"

    #define __rnSocketUDPReserve__   rnWin32SocketUDPReserve
    #define __rnSocketUDPCreate__    rnWin32SocketUDPCreate
    #define __rnSocketUDPDestroy__   rnWin32SocketUDPDestroy
    #define __rnSocketUDPBind__      rnWin32SocketUDPBind
    #define __rnSocketUDPConnect__   rnWin32SocketUDPConnect
    #define __rnSocketUDPWrite__     rnWin32SocketUDPWrite
    #define __rnSocketUDPWriteHost__ rnWin32SocketUDPWriteHost
    #define __rnSocketUDPRead__      rnWin32SocketUDPRead
    #define __rnSocketUDPReadHost__  rnWin32SocketUDPReadHost

#else

    #error "Unknown platform"

#endif

RnSocketUDP*
rnSocketUDPReserve(RnMemoryArena* arena)
{
    return __rnSocketUDPReserve__(arena);
}

b32
rnSocketUDPCreate(RnSocketUDP* self, RnAddressIPKind kind)
{
    return __rnSocketUDPCreate__(self, kind);
}

void
rnSocketUDPDestroy(RnSocketUDP* self)
{
    return __rnSocketUDPDestroy__(self);
}

b32
rnSocketUDPBind(RnSocketUDP* self, u16 port)
{
    return __rnSocketUDPBind__(self, port);
}

b32
rnSocketUDPConnect(RnSocketUDP* self, RnAddressIP address, u16 port)
{
    return __rnSocketUDPConnect__(self, address, port);
}

ssize
rnSocketUDPWrite(RnSocketUDP* self, u8* values, ssize size)
{
    return __rnSocketUDPWrite__(self, values, size);
}

ssize
rnSocketUDPWriteHost(RnSocketUDP* self, u8* values, ssize size, RnAddressIP address, u16 port)
{
    return __rnSocketUDPWriteHost__(self, values, size, address, port);
}

ssize
rnSocketUDPRead(RnSocketUDP* self, u8* values, ssize size)
{
    return __rnSocketUDPRead__(self, values, size);
}

ssize
rnSocketUDPReadHost(RnSocketUDP* self, u8* values, ssize size, RnAddressIP* address, u16* port)
{
    return __rnSocketUDPReadHost__(self, values, size, address, port);
}

#endif // RN_SYSTEM_NETWORK_SOCKET_UDP_C
