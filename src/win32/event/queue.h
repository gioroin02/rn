#ifndef RN_WIN32_EVENT_QUEUE_H
#define RN_WIN32_EVENT_QUEUE_H

#include "./import.h"

typedef struct RnWin32EventQueue RnWin32EventQueue;

b32
rnWin32EventQueueCreate(RnWin32EventQueue* self);

void
rnWin32EventQueueDestroy(RnWin32EventQueue* self);

void
rnWin32EventQueueWake(RnWin32EventQueue* self);

ssize
rnWin32EventQueuePoll(RnWin32EventQueue* self, RnSystemEvent* event, ssize timeout);

b32
rnWin32EventQueueInsertWatcher(RnWin32EventQueue* self, void* handle, RnSystemEventKind mask);

b32
rnWin32EventQueueUpdateWatcher(RnWin32EventQueue* self, void* handle, RnSystemEventKind mask);

b32
rnWin32EventQueueRemoveWatcher(RnWin32EventQueue* self, void* handle);

#endif // RN_WIN32_EVENT_QUEUE_H
