#ifndef RHO_SYSTEM_NETWORK_ASYNC_WIN32_SOCKET_TCP_H
#define RHO_SYSTEM_NETWORK_ASYNC_WIN32_SOCKET_TCP_H

#include "import.h"

typedef struct RWin32SocketTcpAccept
{
    __RWin32IoTaskTag__;

    RWin32SocketTcp* self;
    void*            ctxt;

    RWin32SocketTcp* value;

    RUint8 __buff__[sizeof (RWin32AddrStorage) * 2];
}
RWin32SocketTcpAccept;

typedef struct RWin32SocketTcpConnect
{
    __RWin32IoTaskTag__;

    RWin32SocketTcp* self;
    void*            ctxt;

    RHostIp host;
}
RWin32SocketTcpConnect;

typedef struct RWin32SocketTcpWrite
{
    __RWin32IoTaskTag__;

    RWin32SocketTcp* self;
    void*            ctxt;

    RUint8* pntr;
    RInt    start;
    RInt    stop;
    WSABUF  buffer;
}
RWin32SocketTcpWrite;

typedef struct RWin32SocketTcpRead
{
    __RWin32IoTaskTag__;

    RWin32SocketTcp* self;
    void*            ctxt;

    RUint8* pntr;
    RInt    start;
    RInt    stop;
    WSABUF  buffer;
}
RWin32SocketTcpRead;

RBool32 rho_win32_socket_tcp_async_accept(RWin32SocketTcp* self, RWin32SocketTcp* value, RWin32IoQueue* queue, void* ctxt);

RBool32 rho_win32_socket_tcp_async_connect(RWin32SocketTcp* self, RHostIp host, RWin32IoQueue* queue, void* ctxt);

RBool32 rho_win32_socket_tcp_async_write(RWin32SocketTcp* self, RUint8* pntr, RInt start, RInt stop, RWin32IoQueue* queue, void* ctxt);

RBool32 rho_win32_socket_tcp_async_read(RWin32SocketTcp* self, RUint8* pntr, RInt start, RInt stop, RWin32IoQueue* queue, void* ctxt);

#endif
