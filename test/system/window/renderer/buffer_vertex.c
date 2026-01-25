#ifndef P_GRAPHICS_BUFFER_VERTEX_C
#define P_GRAPHICS_BUFFER_VERTEX_C

#include "buffer_vertex.h"

#include "gl.h"

B32 pBufferVertexCreate(PBufferVertex* self, Int count, Int size)
{
    pMemorySet(self, sizeof *self, 0xAB);

    if (count < 0 || size < 0 || count > P_INT_MAX / size)
        return 0;

    Int handle = 0;
    Int bytes  = count * size;

    glGenBuffers(1, (GLuint*) &handle);

    if (handle == 0) return 0;

    self->handle = handle;
    self->size   = count;
    self->stride = size;

    glBindBuffer(GL_ARRAY_BUFFER, self->handle);

    glBufferData(GL_ARRAY_BUFFER, bytes,
        NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return 1;
}

void pBufferVertexDestroy(PBufferVertex* self)
{
    if (self->handle != 0)
        glDeleteBuffers(1, (GLuint*) &self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

Int pBufferVertexWrite(PBufferVertex* self, U8* pntr, Int start, Int stop)
{
    if (start < 0 || start >= self->size * self->stride) return 0;
    if (stop  < 0 || stop  >= self->size * self->stride) return 0;

    if (stop < start) return 0;

    glBindBuffer(GL_ARRAY_BUFFER, self->handle);

    glBufferSubData(GL_ARRAY_BUFFER, start, stop - start, pntr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return stop - start;
}

#endif
