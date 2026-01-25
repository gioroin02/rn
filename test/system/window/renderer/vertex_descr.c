#ifndef P_GRAPHICS_VERTEX_DESCR_C
#define P_GRAPHICS_VERTEX_DESCR_C

#include "vertex_descr.h"

#include "gl.h"

static PVertexField pVertexFieldMake(PVertexFieldKind kind, Int count)
{
    PVertexField result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.kind  = kind;
    result.count = count;

    return result;
}

static Int pVertexFieldSize(PVertexField* self)
{
    switch (self->kind) {
        case PVertexField_U8:  return self->count * sizeof (U8);
        case PVertexField_U16: return self->count * sizeof (U16);
        case PVertexField_U32: return self->count * sizeof (U32);
        case PVertexField_I8:  return self->count * sizeof (I8);
        case PVertexField_I16: return self->count * sizeof (I16);
        case PVertexField_I32: return self->count * sizeof (I32);
        case PVertexField_F32: return self->count * sizeof (F32);
        case PVertexField_F64: return self->count * sizeof (F64);

        default: break;
    }

    return 0;
}

static GLenum pVertexFieldKind(PVertexField* self)
{
    switch (self->kind) {
        case PVertexField_U8:  return GL_UNSIGNED_BYTE;
        case PVertexField_U16: return GL_UNSIGNED_SHORT;
        case PVertexField_U32: return GL_UNSIGNED_INT;
        case PVertexField_I8:  return GL_BYTE;
        case PVertexField_I16: return GL_SHORT;
        case PVertexField_I32: return GL_INT;
        case PVertexField_F32: return GL_FLOAT;
        case PVertexField_F64: return GL_DOUBLE;

        default: break;
    }

    return 0;
}

B32 pVertexLayoutPush(PVertexLayout* self, PVertexFieldKind kind, Int count)
{
    if (self->count < 0 || self->count >= 16) return 0;

    PVertexField field = pVertexFieldMake(kind, count);

    self->values[self->count]  = field;
    self->count               += 1;

    return 1;
}

B32 pVertexLayoutPop(PVertexLayout* self)
{
    if (self->count <= 0 || self->count > 16)
        return 0;

    self->count -= 1;

    return 1;
}

void pVertexLayoutClear(PVertexLayout* self)
{
    self->count = 0;
}

B32 pVertexDescrCreate(PVertexDescr* self)
{
    pMemorySet(self, sizeof *self, 0xAB);

    Int handle = 0;

    glGenVertexArrays(1, (GLuint*) &handle);

    if (handle == 0) return 0;

    self->handle = handle;

    return 1;
}

void pVertexDescrDestroy(PVertexDescr* self)
{
    if (self->handle != 0)
        glDeleteVertexArrays(1, (GLuint*) &self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

B32 pVertexDescrApplyLayout(PVertexDescr* self, PVertexLayout* layout,
    PBufferVertex* buff_vertex, PBufferIndex* buff_index)
{
    GLenum slot_vertex = GL_ARRAY_BUFFER;
    GLenum slot_index  = GL_ELEMENT_ARRAY_BUFFER;

    Int stride = 0;
    Int offset = 0;

    for (Int i = 0; i < layout->count; i += 1)
        stride += pVertexFieldSize(&layout->values[i]);

    glBindVertexArray(self->handle);

    if (buff_vertex != NULL)
        glBindBuffer(slot_vertex, buff_vertex->handle);

    if (buff_index != NULL)
        glBindBuffer(slot_index, buff_index->handle);

    for (Int i = 0; i < layout->count; i += 1) {
        PVertexField* field = &layout->values[i];
        GLenum           kind  = pVertexFieldKind(field);

        glVertexAttribPointer(i, field->count,
            kind, GL_FALSE, stride, (void*) offset);

        glEnableVertexAttribArray(i);

        offset += pVertexFieldSize(field);
    }

    glBindVertexArray(0);

    glBindBuffer(slot_vertex, 0);
    glBindBuffer(slot_index, 0);

    return 1;
}

#endif
