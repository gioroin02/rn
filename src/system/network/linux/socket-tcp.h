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

B32 pLinuxSocketTcpCreate(PLinuxSocketTcp* self, PHostIp host);

B32 pLinuxSocketTcpAccept(PLinuxSocketTcp* self, PLinuxSocketTcp* value);

void pLinuxSocketTcpDestroy(PLinuxSocketTcp* self);

B32 pLinuxSocketTcpBind(PLinuxSocketTcp* self);

B32 pLinuxSocketTcpBindAs(PLinuxSocketTcp* self, PHostIp host);

B32 pLinuxSocketTcpListen(PLinuxSocketTcp* self);

B32 pLinuxSocketTcpConnect(PLinuxSocketTcp* self, PHostIp host);

Int pLinuxSocketTcpWrite(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop);

Int pLinuxSocketTcpRead(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop);

PHostIp pLinuxSocketTcpGetHost(PLinuxSocketTcp* self);

#endif
