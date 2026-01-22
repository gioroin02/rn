#ifndef P_GRAPHICS_BUFFER_VERTEX_H
#define P_GRAPHICS_BUFFER_VERTEX_H

#include "import.h"

#define pBufferVertexCreateOf(self, type, count) \
    (pBufferVertexCreate(self, count, sizeof (type)))

typedef struct PBufferVertex
{
    Int handle;
    Int size;
    Int stride;
}
PBufferVertex;

Bool pBufferVertexCreate(PBufferVertex* self, Int count, Int size);

void pBufferVertexDestroy(PBufferVertex* self);

Int pBufferVertexWrite(PBufferVertex* self, U8* pntr, Int start, Int stop);

#endif // P_GRAPHICS_BUFFER_VERTEX_H
