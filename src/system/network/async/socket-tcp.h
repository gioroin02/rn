#ifndef P_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_H
#define P_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_H

#include "import.h"

typedef enum PSocketTcpEventKind
{
    PSocketTcpEvent_None,
    PSocketTcpEvent_Accept,
    PSocketTcpEvent_Connect,
    PSocketTcpEvent_Write,
    PSocketTcpEvent_Read,
}
PSocketTcpEventKind;

typedef struct PSocketTcpEventAccept
{
    void*       ctxt;
    PSocketTcp* socket;
    PSocketTcp* value;
}
PSocketTcpEventAccept;

typedef struct PSocketTcpEventConnect
{
    void*       ctxt;
    PSocketTcp* socket;
    PHostIp     host;
    Bool        status;
}
PSocketTcpEventConnect;

typedef struct PSocketTcpEventWrite
{
    void*       ctxt;
    PSocketTcp* socket;
    U8*         pntr;
    Int         start;
    Int         stop;
    Int         bytes;
}
PSocketTcpEventWrite;

typedef struct PSocketTcpEventRead
{
    void*       ctxt;
    PSocketTcp* socket;
    U8*         pntr;
    Int         start;
    Int         stop;
    Int         bytes;
}
PSocketTcpEventRead;

typedef struct PSocketTcpEvent
{
    PSocketTcpEventKind kind;

    union
    {
        PSocketTcpEventAccept  accept;
        PSocketTcpEventConnect connect;
        PSocketTcpEventWrite   write;
        PSocketTcpEventRead    read;
    };
}
PSocketTcpEvent;

PSocketTcpEvent pSocketTcpEventAccept(PSocketTcp* self, PSocketTcp* value, void* ctxt);

PSocketTcpEvent pSocketTcpEventConnect(PSocketTcp* self, PHostIp host, Bool status, void* ctxt);

PSocketTcpEvent pSocketTcpEventWrite(PSocketTcp* self, U8* pntr, Int start, Int stop, Int bytes, void* ctxt);

PSocketTcpEvent pSocketTcpEventRead(PSocketTcp* self, U8* pntr, Int start, Int stop, Int bytes, void* ctxt);

Bool pSocketTcpAcceptAsync(PSocketTcp* self, PSocketTcp* value, PAsyncIoQueue* queue, void* ctxt);

Bool pSocketTcpConnectAsync(PSocketTcp* self, PHostIp host, PAsyncIoQueue* queue, void* ctxt);

Bool pSocketTcpWriteAsync(PSocketTcp* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt);

Bool pSocketTcpReadAsync(PSocketTcp* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt);

#endif
