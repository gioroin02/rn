#ifndef P_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_H
#define P_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_H

#include "import.h"

typedef void (PSocketTcpAcceptProc)  (void*, PSocketTcp*, PSocketTcp*);
typedef void (PSocketTcpConnectProc) (void*, PSocketTcp*, PHostIp, Bool);
typedef void (PSocketTcpWriteProc)   (void*, PSocketTcp*, U8*, Int, Int, Int);
typedef void (PSocketTcpReadProc)    (void*, PSocketTcp*, U8*, Int, Int, Int);

Bool pSocketTcpAcceptAsync(PSocketTcp* self, PSocketTcp* value, PAsyncIoQueue* queue, void* ctxt, void* proc);

Bool pSocketTcpConnectAsync(PSocketTcp* self, PHostIp host, PAsyncIoQueue* queue, void* ctxt, void* proc);

Bool pSocketTcpWriteAsync(PSocketTcp* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt, void* proc);

Bool pSocketTcpReadAsync(PSocketTcp* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt, void* proc);

#endif // P_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_H
