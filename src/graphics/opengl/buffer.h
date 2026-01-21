#ifndef P_GRAPHICS_OPENGL_BUFFER_H
#define P_GRAPHICS_OPENGL_BUFFER_H

#include "import.h"

#define pOglBufferVertexCreateOf(self, type, count) \
    (pOglBufferVertexCreate(self, count, sizeof (type)))

typedef struct POglBufferVertex
{
    Int handle;
    Int size;
    Int stride;
}
POglBufferVertex;

Bool pOglBufferVertexCreate(POglBufferVertex* self, Int count, Int size);

void pOglBufferVertexDestroy(POglBufferVertex* self);

Int pOglBufferVertexWrite(POglBufferVertex* self, U8* pntr, Int start, Int stop);

#endif // P_GRAPHICS_OPENGL_BUFFER_H
