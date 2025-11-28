#ifndef RN_SYSTEM_EVENT_COMMON_C
#define RN_SYSTEM_EVENT_COMMON_C

#include "./common.h"

RnSystemEvent
rnSystemEventMake(RnSystemEventKind mask, void* handle, ssize size)
{
    return (RnSystemEvent) {
        .kind   = mask,
        .handle = handle,
        .size   = size,
    };
}

#endif // RN_SYSTEM_EVENT_COMMON_C
