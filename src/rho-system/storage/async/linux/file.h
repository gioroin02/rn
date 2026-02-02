#ifndef RHO_SYSTEM_LINUX_STORAGE_ASYNC_FILE_H
#define RHO_SYSTEM_LINUX_STORAGE_ASYNC_FILE_H

#include "import.h"

typedef struct RLinuxFileWrite
{
    __RLinuxIoTaskTag__;

    RLinuxFile* self;
    void*       ctxt;

    RUint8* pntr;
    RInt    start;
    RInt    stop;
}
RLinuxFileWrite;

typedef struct RLinuxFileRead
{
    __RLinuxIoTaskTag__;

    RLinuxFile* self;
    void*       ctxt;

    RUint8* pntr;
    RInt    start;
    RInt    stop;
}
RLinuxFileRead;

RBool32 rho_linux_file_async_write(RLinuxFile* self, RUint8* pntr, RInt start, RInt stop, RLinuxIoQueue* queue, void* ctxt);

RBool32 rho_linux_file_async_read(RLinuxFile* self, RUint8* pntr, RInt start, RInt stop, RLinuxIoQueue* queue, void* ctxt);

#endif
