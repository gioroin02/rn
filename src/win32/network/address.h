#ifndef PX_WIN32_NETWORK_ADDRESS_H
#define PX_WIN32_NETWORK_ADDRESS_H

#include "common.h"

PxSockAddrStorage
pxSockAddrStorageMake(PxAddressIP address, u16 port, ssize* size);

PxSockAddrStorage
pxSockAddrStorageMakeAny(PxAddressIPKind kind, u16 port, ssize* size);

PxAddressIP
pxSockAddrStorageGetAddress(PxSockAddrStorage* self);

u16
pxSockAddrStorageGetPort(PxSockAddrStorage* self);

#endif // PX_WIN32_NETWORK_ADDRESS_H
