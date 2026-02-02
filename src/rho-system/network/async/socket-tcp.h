#ifndef RHO_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_H
#define RHO_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_H

#include "import.h"

typedef enum RSocketTcpEventKind
{
    RSocketTcpEvent_None,
    RSocketTcpEvent_Accept,
    RSocketTcpEvent_Connect,
    RSocketTcpEvent_Write,
    RSocketTcpEvent_Read,
}
RSocketTcpEventKind;

typedef struct RSocketTcpEventAccept
{
    void*       ctxt;
    RSocketTcp* socket;
    RSocketTcp* value;
}
RSocketTcpEventAccept;

typedef struct RSocketTcpEventConnect
{
    void*       ctxt;
    RSocketTcp* socket;
    RHostIp     host;
    RBool32     status;
}
RSocketTcpEventConnect;

typedef struct RSocketTcpEventWrite
{
    void*       ctxt;
    RSocketTcp* socket;
    RUint8*     pntr;
    RInt        start;
    RInt        stop;
    RInt        bytes;
}
RSocketTcpEventWrite;

typedef struct RSocketTcpEventRead
{
    void*       ctxt;
    RSocketTcp* socket;
    RUint8*     pntr;
    RInt        start;
    RInt        stop;
    RInt        bytes;
}
RSocketTcpEventRead;

typedef struct RSocketTcpEvent
{
    RIoEventFamily      family;
    RSocketTcpEventKind kind;

    union
    {
        RSocketTcpEventAccept  accept;
        RSocketTcpEventConnect connect;
        RSocketTcpEventWrite   write;
        RSocketTcpEventRead    read;
    };
}
RSocketTcpEvent;

RSocketTcpEvent rho_socket_tcp_event_accept(RSocketTcp* self, RSocketTcp* value, void* ctxt);

RSocketTcpEvent rho_socket_tcp_event_connect(RSocketTcp* self, RHostIp host, RBool32 status, void* ctxt);

RSocketTcpEvent rho_socket_tcp_event_write(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RInt bytes, void* ctxt);

RSocketTcpEvent rho_socket_tcp_event_read(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RInt bytes, void* ctxt);

RBool32 rho_socket_tcp_async_accept(RSocketTcp* self, RSocketTcp* value, RIoQueue* queue, void* ctxt);

RBool32 rho_socket_tcp_async_connect(RSocketTcp* self, RHostIp host, RIoQueue* queue, void* ctxt);

RBool32 rho_socket_tcp_async_write(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RIoQueue* queue, void* ctxt);

RBool32 rho_socket_tcp_async_read(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RIoQueue* queue, void* ctxt);

#endif
