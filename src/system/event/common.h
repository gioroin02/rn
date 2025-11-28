#ifndef RN_SYSTEM_EVENT_COMMON_H
#define RN_SYSTEM_EVENT_COMMON_H

#include "./import.h"

#define rnSystemEventNone()  ((RnSystemEvent) {.kind = RnSystemEvent_None})
#define rnSystemEventError() ((RnSystemEvent) {.kind = RnSystemEvent_Error})

typedef enum RnSystemEventKind
{
    RnSystemEvent_None,
    RnSystemEvent_Read,
    RnSystemEvent_Write,
    RnSystemEvent_Close,
    RnSystemEvent_Error,
}
RnSystemEventKind;

typedef struct RnSystemEvent
{
    RnSystemEventKind kind;

    void* handle;
    ssize size;
}
RnSystemEvent;

RnSystemEvent
rnSystemEventMake(RnSystemEventKind mask, void* handle, ssize size);

#endif // RN_SYSTEM_EVENT_COMMON_H
