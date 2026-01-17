#ifndef P_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_C
#define P_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_C

#include "socket-tcp.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PAsyncIoQueue__ PWin32AsyncIoQueue
    #define __PSocketTcp__    PWin32SocketTcp

    #define __pSocketTcpAcceptAsync__  pWin32SocketTcpAcceptAsync
    #define __pSocketTcpConnectAsync__ pWin32SocketTcpConnectAsync
    #define __pSocketTcpWriteAsync__   pWin32SocketTcpWriteAsync
    #define __pSocketTcpReadAsync__    pWin32SocketTcpReadAsync

#else

    #error "Unknown platform"

#endif

Bool pSocketTcpAcceptAsync(PSocketTcp* self, PSocketTcp* value, PAsyncIoQueue* queue, void* ctxt, void* proc)
{
    return __pSocketTcpAcceptAsync__((__PSocketTcp__*) self, (__PSocketTcp__*) value, (__PAsyncIoQueue__*) queue, ctxt, proc);
}

Bool pSocketTcpConnectAsync(PSocketTcp* self, PHostIp host, PAsyncIoQueue* queue, void* ctxt, void* proc)
{
    return __pSocketTcpConnectAsync__((__PSocketTcp__*) self, host, (__PAsyncIoQueue__*) queue, ctxt, proc);
}

Bool pSocketTcpWriteAsync(PSocketTcp* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt, void* proc)
{
    return __pSocketTcpWriteAsync__((__PSocketTcp__*) self, pntr, start, stop, (__PAsyncIoQueue__*) queue, ctxt, proc);
}

Bool pSocketTcpReadAsync(PSocketTcp* self, U8* pntr, Int start, Int stop, PAsyncIoQueue* queue, void* ctxt, void* proc)
{
    return __pSocketTcpReadAsync__((__PSocketTcp__*) self, pntr, start, stop, (__PAsyncIoQueue__*) queue, ctxt, proc);
}

#endif // P_SYSTEM_NETWORK_ASYNC_SOCKET_TCP_C
