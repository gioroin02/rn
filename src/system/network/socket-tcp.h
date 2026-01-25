#ifndef P_SYSTEM_NETWORK_SOCKET_TCP_H
#define P_SYSTEM_NETWORK_SOCKET_TCP_H

#include "address-ip.h"

typedef struct PSocketTcp { U8 __private__; } PSocketTcp;

PSocketTcp* pSocketTcpReserve(PMemoryArena* arena);

B32 pSocketTcpCreate(PSocketTcp* self, PHostIp host);

B32 pSocketTcpAccept(PSocketTcp* self, PSocketTcp* value);

void pSocketTcpDestroy(PSocketTcp* self);

B32 pSocketTcpBind(PSocketTcp* self);

B32 pSocketTcpBindAs(PSocketTcp* self, PHostIp host);

B32 pSocketTcpListen(PSocketTcp* self);

B32 pSocketTcpConnect(PSocketTcp* self, PHostIp host);

Int pSocketTcpWrite(PSocketTcp* self, U8* pntr, Int start, Int stop);

Int pSocketTcpRead(PSocketTcp* self, U8* pntr, Int start, Int stop);

PHostIp pSocketTcpGetHost(PSocketTcp* self);

#endif
