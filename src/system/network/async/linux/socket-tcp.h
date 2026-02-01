#ifndef RHO_SYSTEM_NETWORK_LINUX_ASYNC_SOCKET_TCP_H
#define RHO_SYSTEM_NETWORK_LINUX_ASYNC_SOCKET_TCP_H

#include "import.h"

typedef struct RLinuxSocketTcpAccept
{
    __RLinuxIoTaskTag__;

    RLinuxSocketTcp* self;
    void*            ctxt;

    RLinuxSocketTcp* value;
}
RLinuxSocketTcpAccept;

typedef struct RLinuxSocketTcpConnect
{
    __RLinuxIoTaskTag__;

    RLinuxSocketTcp* self;
    void*            ctxt;

    RHostIp host;
}
RLinuxSocketTcpConnect;

typedef struct RLinuxSocketTcpWrite
{
    __RLinuxIoTaskTag__;

    RLinuxSocketTcp* self;
    void*            ctxt;

    RUint8* pntr;
    RInt    start;
    RInt    stop;
}
RLinuxSocketTcpWrite;

typedef struct RLinuxSocketTcpRead
{
    __RLinuxIoTaskTag__;

    RLinuxSocketTcp* self;
    void*            ctxt;

    RUint8* pntr;
    RInt    start;
    RInt    stop;
}
RLinuxSocketTcpRead;

RBool32 rho_linux_socket_tcp_async_accept(RLinuxSocketTcp* self, RLinuxSocketTcp* value, RLinuxIoQueue* queue, void* ctxt);

RBool32 rho_linux_socket_tcp_async_connect(RLinuxSocketTcp* self, RHostIp host, RLinuxIoQueue* queue, void* ctxt);

RBool32 rho_linux_socket_tcp_async_write(RLinuxSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RLinuxIoQueue* queue, void* ctxt);

RBool32 rho_linux_socket_tcp_async_read(RLinuxSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RLinuxIoQueue* queue, void* ctxt);

#endif
