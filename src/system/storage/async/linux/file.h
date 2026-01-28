#ifndef P_SYSTEM_LINUX_STORAGE_ASYNC_FILE_H
#define P_SYSTEM_LINUX_STORAGE_ASYNC_FILE_H

#include "import.h"

typedef struct PLinuxFileWrite
{
    __PLinuxAsyncIoTaskTag__;

    PLinuxFile* self;
    void*       ctxt;

    U8* pntr;
    Int start;
    Int stop;
}
PLinuxFileWrite;

typedef struct PLinuxFileRead
{
    __PLinuxAsyncIoTaskTag__;

    PLinuxFile* self;
    void*       ctxt;

    U8* pntr;
    Int start;
    Int stop;
}
PLinuxFileRead;

B32 pLinuxFileWriteAsync(PLinuxFile* self, U8* pntr, Int start, Int stop, PLinuxAsyncIoQueue* queue, void* ctxt);

B32 pLinuxFileReadAsync(PLinuxFile* self, U8* pntr, Int start, Int stop, PLinuxAsyncIoQueue* queue, void* ctxt);

#endif
