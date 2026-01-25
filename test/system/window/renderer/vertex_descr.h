#ifndef P_GRAPHICS_VERTEX_DESCR_H
#define P_GRAPHICS_VERTEX_DESCR_H

#include "buffer_vertex.h"
#include "buffer_index.h"

typedef enum PVertexFieldKind
{
    PVertexField_None,

    PVertexField_U8,
    PVertexField_U16,
    PVertexField_U32,

    PVertexField_I8,
    PVertexField_I16,
    PVertexField_I32,

    PVertexField_F32,
    PVertexField_F64,
}
PVertexFieldKind;

typedef struct PVertexField
{
    PVertexFieldKind kind;

    Int count;
}
PVertexField;

typedef struct PVertexLayout
{
    PVertexField values[16];

    Int count;
}
PVertexLayout;

typedef struct PVertexDescr
{
    Int handle;
}
PVertexDescr;

B32 pVertexLayoutPush(PVertexLayout* self, PVertexFieldKind kind, Int count);

B32 pVertexLayoutPop(PVertexLayout* self);

void pVertexLayoutClear(PVertexLayout* self);

B32 pVertexDescrCreate(PVertexDescr* self);

void pVertexDescrDestroy(PVertexDescr* self);

B32 pVertexDescrApplyLayout(PVertexDescr* self, PVertexLayout* layout,
    PBufferVertex* buff_vertex, PBufferIndex* buff_index);

#endif
