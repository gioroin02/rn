#ifndef P_SYSTEM_LINUX_NETWORK_ASYNC_SOCKET_TCP_H
#define P_SYSTEM_LINUX_NETWORK_ASYNC_SOCKET_TCP_H

#include "import.h"

typedef struct PLinuxSocketTcpAccept
{
    __PLinuxAsyncIoTaskTag__;

    PLinuxSocketTcp* self;
    void*            ctxt;

    PLinuxSocketTcp* value;
}
PLinuxSocketTcpAccept;

typedef struct PLinuxSocketTcpConnect
{
    __PLinuxAsyncIoTaskTag__;

    PLinuxSocketTcp* self;
    void*            ctxt;

    PHostIp host;
}
PLinuxSocketTcpConnect;

typedef struct PLinuxSocketTcpWrite
{
    __PLinuxAsyncIoTaskTag__;

    PLinuxSocketTcp* self;
    void*            ctxt;

    U8* pntr;
    Int start;
    Int stop;
}
PLinuxSocketTcpWrite;

typedef struct PLinuxSocketTcpRead
{
    __PLinuxAsyncIoTaskTag__;

    PLinuxSocketTcp* self;
    void*            ctxt;

    U8* pntr;
    Int start;
    Int stop;
}
PLinuxSocketTcpRead;

B32 pLinuxSocketTcpAcceptAsync(PLinuxSocketTcp* self, PLinuxSocketTcp* value, PLinuxAsyncIoQueue* queue, void* ctxt);

B32 pLinuxSocketTcpConnectAsync(PLinuxSocketTcp* self, PHostIp host, PLinuxAsyncIoQueue* queue, void* ctxt);

B32 pLinuxSocketTcpWriteAsync(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop, PLinuxAsyncIoQueue* queue, void* ctxt);

B32 pLinuxSocketTcpReadAsync(PLinuxSocketTcp* self, U8* pntr, Int start, Int stop, PLinuxAsyncIoQueue* queue, void* ctxt);

#endif
