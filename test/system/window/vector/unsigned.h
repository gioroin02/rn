#ifndef VECTOR_UNSIGNED_H
#define VECTOR_UNSIGNED_H

#include "import.h"

#define u8v2(x, y)       ((U8Vec2) {(x), (y)})
#define u8v3(x, y, z)    ((U8Vec3) {(x), (y), (z)})
#define u8v4(x, y, z, w) ((U8Vec4) {(x), (y), (z), (w)})

#define u16v2(x, y)       ((U16Vec2) {(x), (y)})
#define u16v3(x, y, z)    ((U16Vec3) {(x), (y), (z)})
#define u16v4(x, y, z, w) ((U16Vec4) {(x), (y), (z), (w)})

#define u32v2(x, y)       ((U32Vec2) {(x), (y)})
#define u32v3(x, y, z)    ((U32Vec3) {(x), (y), (z)})
#define u32v4(x, y, z, w) ((U32Vec4) {(x), (y), (z), (w)})

#define u64v2(x, y)       ((U64Vec2) {(x), (y)})
#define u64v3(x, y, z)    ((U64Vec3) {(x), (y), (z)})
#define u64v4(x, y, z, w) ((U64Vec4) {(x), (y), (z), (w)})

typedef union U8Vec2
{
    U8 values[2];

    struct { U8  x,  y; };
    struct { U8  r,  g; };
    struct { U8 v0, v1; };
}
U8Vec2;

typedef union U8Vec3
{
    U8 values[3];

    struct { U8Vec2 xy; U8 _1; };
    struct { U8 _2; U8Vec2 yz; };

    struct { U8  x,  y,  z; };
    struct { U8  r,  g,  b; };
    struct { U8 v0, v1, v2; };
}
U8Vec3;

typedef union U8Vec4
{
    U8 values[4];

    struct { U8Vec2 xy; U8Vec2 zw; };
    struct { U8 _1; U8Vec2 yz; U8 _2; };

    struct { U8Vec3 xyz; U8 _3; };
    struct { U8 _4; U8Vec3 yzw; };

    struct { U8  x,  y,  z,  w; };
    struct { U8  r,  g,  b,  a; };
    struct { U8 v0, v1, v2, v3; };
}
U8Vec4;

typedef union U16Vec2
{
    U16 values[2];

    struct { U16  x,  y; };
    struct { U16  r,  g; };
    struct { U16 v0, v1; };
}
U16Vec2;

typedef union U16Vec3
{
    U16 values[3];

    struct { U16Vec2 xy; U16 _1; };
    struct { U16 _2; U16Vec2 yz; };

    struct { U16  x,  y,  z; };
    struct { U16  r,  g,  b; };
    struct { U16 v0, v1, v2; };
}
U16Vec3;

typedef union U16Vec4
{
    U16 values[4];

    struct { U16Vec2 xy; U16Vec2 zw; };
    struct { U16 _1; U16Vec2 yz; U16 _2; };

    struct { U16Vec3 xyz; U16 _3; };
    struct { U16 _4; U16Vec3 yzw; };

    struct { U16  x,  y,  z,  w; };
    struct { U16  r,  g,  b,  a; };
    struct { U16 v0, v1, v2, v3; };
}
U16Vec4;

typedef union U32Vec2
{
    U32 values[2];

    struct { U32  x,  y; };
    struct { U32  r,  g; };
    struct { U32 v0, v1; };
}
U32Vec2;

typedef union U32Vec3
{
    U32 values[3];

    struct { U32Vec2 xy; U32 _1; };
    struct { U32 _2; U32Vec2 yz; };

    struct { U32  x,  y,  z; };
    struct { U32  r,  g,  b; };
    struct { U32 v0, v1, v2; };
}
U32Vec3;

typedef union U32Vec4
{
    U32 values[4];

    struct { U32Vec2 xy; U32Vec2 zw; };
    struct { U32 _1; U32Vec2 yz; U32 _2; };

    struct { U32Vec3 xyz; U32 _3; };
    struct { U32 _4; U32Vec3 yzw; };

    struct { U32  x,  y,  z,  w; };
    struct { U32  r,  g,  b,  a; };
    struct { U32 v0, v1, v2, v3; };
}
U32Vec4;

typedef union U64Vec2
{
    U64 values[2];

    struct { U64  x,  y; };
    struct { U64  r,  g; };
    struct { U64 v0, v1; };
}
U64Vec2;

typedef union U64Vec3
{
    U64 values[3];

    struct { U64Vec2 xy; U64 _1; };
    struct { U64 _2; U64Vec2 yz; };

    struct { U64  x,  y,  z; };
    struct { U64  r,  g,  b; };
    struct { U64 v0, v1, v2; };
}
U64Vec3;

typedef union U64Vec4
{
    U64 values[4];

    struct { U64Vec2 xy; U64Vec2 zw; };
    struct { U64 _1; U64Vec2 yz; U64 _2; };

    struct { U64Vec3 xyz; U64 _3; };
    struct { U64 _4; U64Vec3 yzw; };

    struct { U64  x,  y,  z,  w; };
    struct { U64  r,  g,  b,  a; };
    struct { U64 v0, v1, v2, v3; };
}
U64Vec4;

#endif // VECTOR_UNSIGNED_H
