#ifndef RHO_SYSTEM_ASYNCIO_QUEUE_H
#define RHO_SYSTEM_ASYNCIO_QUEUE_H

#include "import.h"

typedef enum RIoEventFamily
{
    RIoEventFamily_None,
    RIoEventFamily_File,
    RIoEventFamily_Tcp,
    RIoEventFamily_Udp,
}
RIoEventFamily;

typedef struct RIoEvent
{
    RIoEventFamily family;
}
RIoEvent;

typedef struct RIoQueue { RUint8 __private__; } RIoQueue;

RIoQueue* rho_io_queue_reserve(RMemoryArena* arena);

RBool32 rho_io_queue_create(RIoQueue* self, RMemoryPool pool);

void rho_io_queue_destroy(RIoQueue* self);

RIoEvent* rho_io_queue_poll_event(RIoQueue* self, RInt timeout, RMemoryArena* arena);

#endif
