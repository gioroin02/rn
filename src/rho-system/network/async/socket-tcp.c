#ifndef RHO_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_C
#define RHO_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_C

#include "socket-tcp.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RIoQueue__   RWin32IoQueue
    #define __RSocketTcp__ RWin32SocketTcp

    #define __rho_socket_tcp_async_accept__  rho_win32_socket_tcp_async_accept
    #define __rho_socket_tcp_async_connect__ rho_win32_socket_tcp_async_connect
    #define __rho_socket_tcp_async_write__   rho_win32_socket_tcp_async_write
    #define __rho_socket_tcp_async_read__    rho_win32_socket_tcp_async_read

#elif RHO_SYSTEM == RHO_SYSTEM_LINUX

    #include "linux/export.c"

    #define __RIoQueue__   RLinuxIoQueue
    #define __RSocketTcp__ RLinuxSocketTcp

    #define __rho_socket_tcp_async_accept__  rho_linux_socket_tcp_async_accept
    #define __rho_socket_tcp_async_connect__ rho_linux_socket_tcp_async_connect
    #define __rho_socket_tcp_async_write__   rho_linux_socket_tcp_async_write
    #define __rho_socket_tcp_async_read__    rho_linux_socket_tcp_async_read


#else

    #error "Unknown platform"

#endif

RSocketTcpEvent rho_socket_tcp_event_accept(RSocketTcp* self, RSocketTcp* value, void* ctxt)
{
    RSocketTcpEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.family        = RIoEventFamily_Tcp;
    result.kind          = RSocketTcpEvent_Accept;
    result.accept.ctxt   = ctxt;
    result.accept.socket = self;
    result.accept.value  = value;

    return result;
}

RSocketTcpEvent rho_socket_tcp_event_connect(RSocketTcp* self, RHostIp host, RBool32 status, void* ctxt)
{
    RSocketTcpEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.family         = RIoEventFamily_Tcp;
    result.kind           = RSocketTcpEvent_Connect;
    result.connect.ctxt   = ctxt;
    result.connect.socket = self;
    result.connect.host   = host;
    result.connect.status = status != 0 ? 1 : 0;

    return result;
}

RSocketTcpEvent rho_socket_tcp_event_write(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RInt bytes, void* ctxt)
{
    RSocketTcpEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.family       = RIoEventFamily_Tcp;
    result.kind         = RSocketTcpEvent_Write;
    result.write.ctxt   = ctxt;
    result.write.socket = self;
    result.write.pntr   = pntr;
    result.write.start  = start;
    result.write.stop   = stop;
    result.write.bytes  = bytes;

    return result;
}

RSocketTcpEvent rho_socket_tcp_event_read(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RInt bytes, void* ctxt)
{
    RSocketTcpEvent result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.family      = RIoEventFamily_Tcp;
    result.kind        = RSocketTcpEvent_Read;
    result.read.ctxt   = ctxt;
    result.read.socket = self;
    result.read.pntr   = pntr;
    result.read.start  = start;
    result.read.stop   = stop;
    result.read.bytes  = bytes;

    return result;
}

RBool32 rho_socket_tcp_async_accept(RSocketTcp* self, RSocketTcp* value, RIoQueue* queue, void* ctxt)
{
    return __rho_socket_tcp_async_accept__((__RSocketTcp__*) self, (__RSocketTcp__*) value, (__RIoQueue__*) queue, ctxt);
}

RBool32 rho_socket_tcp_async_connect(RSocketTcp* self, RHostIp host, RIoQueue* queue, void* ctxt)
{
    return __rho_socket_tcp_async_connect__((__RSocketTcp__*) self, host, (__RIoQueue__*) queue, ctxt);
}

RBool32 rho_socket_tcp_async_write(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RIoQueue* queue, void* ctxt)
{
    return __rho_socket_tcp_async_write__((__RSocketTcp__*) self, pntr, start, stop, (__RIoQueue__*) queue, ctxt);
}

RBool32 rho_socket_tcp_async_read(RSocketTcp* self, RUint8* pntr, RInt start, RInt stop, RIoQueue* queue, void* ctxt)
{
    return __rho_socket_tcp_async_read__((__RSocketTcp__*) self, pntr, start, stop, (__RIoQueue__*) queue, ctxt);
}

#endif
