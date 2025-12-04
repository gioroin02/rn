#ifndef RN_WIN32_NETWORK_COMMON_C
#define RN_WIN32_NETWORK_COMMON_C

#include "./common.h"

LPFN_CONNECTEX            connectEx            = 0;
LPFN_ACCEPTEX             acceptEx             = 0;
LPFN_GETACCEPTEXSOCKADDRS getAcceptExSockAddrs = 0;

b32
rnWin32NetworkStart()
{
    WSADATA data = {0};

    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) return 0;

    SOCKET handle = WSASocket(AF_INET,
        SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);

    if (handle == INVALID_SOCKET) return 0;

    DWORD  bytes = 0;

    // TODO(gio): Create an array of GUID and an array of function pointers and loop over them.

    GUID guidConnectEx            = WSAID_CONNECTEX;
    GUID guidAcceptEx             = WSAID_ACCEPTEX;
    GUID guidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;

    WSAIoctl(handle, SIO_GET_EXTENSION_FUNCTION_POINTER,
        &guidConnectEx, sizeof(guidConnectEx),
        &connectEx, sizeof(connectEx), &bytes, 0, 0);

    WSAIoctl(handle, SIO_GET_EXTENSION_FUNCTION_POINTER,
        &guidAcceptEx, sizeof(guidAcceptEx),
        &acceptEx, sizeof(acceptEx), &bytes, 0, 0);

    WSAIoctl(handle, SIO_GET_EXTENSION_FUNCTION_POINTER,
        &guidGetAcceptExSockAddrs, sizeof(guidGetAcceptExSockAddrs),
        &getAcceptExSockAddrs, sizeof(getAcceptExSockAddrs), &bytes, 0, 0);

    closesocket(handle);

    if (connectEx != 0 && acceptEx != 0 && getAcceptExSockAddrs != 0)
        return 1;

    WSACleanup();

    return 0;
}

void
rnWin32NetworkStop()
{
    WSACleanup();
}

#endif // RN_WIN32_NETWORK_COMMON_C
