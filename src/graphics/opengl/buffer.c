#ifndef P_GRAPHICS_OPENGL_BUFFER_C
#define P_GRAPHICS_OPENGL_BUFFER_C

#include "buffer.h"

#include "glad.h"

Bool pOglBufferVertexCreate(POglBufferVertex* self, Int count, Int size)
{
    pMemorySet(self, sizeof *self, 0xAB);

    if (count < 0 || size < 0 || count > P_INT_MAX / size)
        return 0;

    glGenBuffers(1, (GLuint*) &self->handle);

    Int bytes = count * size;

    glBindBuffer(GL_ARRAY_BUFFER, self->handle);

    glBufferData(GL_ARRAY_BUFFER, bytes,
        NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    self->size   = count;
    self->stride = size;

    return 1;
}

void pOglBufferVertexDestroy(POglBufferVertex* self)
{
    if (glIsBuffer(self->handle) != 0)
        glDeleteBuffers(1, (GLuint*) &self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

Int pOglBufferVertexWrite(POglBufferVertex* self, U8* pntr, Int start, Int stop)
{
    if (start < 0 || start >= self->size * self->stride) return 0;
    if (stop  < 0 || stop  >= self->size * self->stride) return 0;

    if (stop < start) return 0;

    glBindBuffer(GL_ARRAY_BUFFER, self->handle);

    glBufferSubData(GL_ARRAY_BUFFER, start, stop - start, pntr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return stop - start;
}

#endif // P_GRAPHICS_OPENGL_BUFFER_C
