#ifndef P_GRAPHICS_BUFFER_INDEX_H
#define P_GRAPHICS_BUFFER_INDEX_H

#include "import.h"

#define pBufferIndexCreateOf(self, type, count) \
    (pBufferIndexCreate(self, count, sizeof (type)))

typedef struct PBufferIndex
{
    Int handle;
    Int size;
    Int stride;
}
PBufferIndex;

B32 pBufferIndexCreate(PBufferIndex* self, Int count, Int size);

void pBufferIndexDestroy(PBufferIndex* self);

Int pBufferIndexWrite(PBufferIndex* self, U8* pntr, Int start, Int stop);

#endif
