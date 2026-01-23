#ifndef P_SYSTEM_LINUX_NETWORK_SOCKET_TCP_H
#define P_SYSTEM_LINUX_NETWORK_SOCKET_TCP_H

#include "common.h"

typedef struct PLinuxSocketTcp
{
    Int               handle;
    PLinuxAddrStorage storage;
}
PLinuxSocketTcp;

PLinuxSocketTcp* pLinuxSocketTcpReserve(PMemoryArena* arena);

Bool pLinuxSocketTcpCreate(PLinuxSocketTcp* self, PHostIp host);

Bool pLinuxSocketTcpAccept(PLinuxSocketTcp* self, PLinuxSocketTcp* value);

void pLinuxSocketTcpDestroy(PLinuxSocketTcp* self);

Bool pLinuxSocketTcpBind(PLinuxSocketTcp* self);

Bool pLinuxSocketTcpBindAs(PLinuxSocketTcp* self, PHostIp host);

Bool pLinuxSocketTcpListen(PLinuxSocketTcp* self);

Bool pLinuxSocketTcpConnect(PLinuxSocketTcp* self, PHostIp host);

Int pLinuxSocketTcpWrite(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop);

Int pLinuxSocketTcpRead(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop);

PHostIp pLinuxSocketTcpGetHost(PLinuxSocketTcp* self);

#endif
