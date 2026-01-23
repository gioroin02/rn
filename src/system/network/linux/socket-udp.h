#ifndef P_SYSTEM_LINUX_NETWORK_SOCKET_UDP_H
#define P_SYSTEM_LINUX_NETWORK_SOCKET_UDP_H

#include "common.h"

typedef struct PLinuxSocketUdp
{
    Int               handle;
    PLinuxAddrStorage storage;
}
PLinuxSocketUdp;

PLinuxSocketUdp* pLinuxSocketUdpReserve(PMemoryArena* arena);

Bool pLinuxSocketUdpCreate(PLinuxSocketUdp* self, PHostIp host);

void pLinuxSocketUdpDestroy(PLinuxSocketUdp* self);

Bool pLinuxSocketUdpBind(PLinuxSocketUdp* self);

Bool pLinuxSocketUdpBindAs(PLinuxSocketUdp* self, PHostIp host);

Int pLinuxSocketUdpWrite(PLinuxSocketUdp* self, U8* pntr, Int start, Int stop, PHostIp host);

Int pLinuxSocketUdpRead(PLinuxSocketUdp* self, U8* pntr, Int start, Int stop, PHostIp* host);

PHostIp pLinuxSocketUdpGetHost(PLinuxSocketUdp* self);

#endif
