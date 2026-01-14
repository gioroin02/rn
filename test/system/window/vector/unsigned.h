#ifndef VECTOR_UNSIGNED_H
#define VECTOR_UNSIGNED_H

#include "import.h"

typedef union U8Vec2
{
    u8 values[2];

    struct { u8  x,  y; };
    struct { u8  r,  g; };
    struct { u8 v0, v1; };
}
U8Vec2;

typedef union U8Vec3
{
    u8 values[3];

    struct { U8Vec2 xy; u8 _1; };
    struct { u8 _2; U8Vec2 yz; };

    struct { u8  x,  y,  z; };
    struct { u8  r,  g,  b; };
    struct { u8 v0, v1, v2; };
}
U8Vec3;

typedef union U8Vec4
{
    u8 values[4];

    struct { U8Vec2 xy; U8Vec2 zw; };
    struct { u8 _1; U8Vec2 yz; u8 _2; };

    struct { U8Vec3 xyz; u8 _3; };
    struct { u8 _4; U8Vec3 yzw; };

    struct { u8  x,  y,  z,  w; };
    struct { u8  r,  g,  b,  a; };
    struct { u8 v0, v1, v2, v3; };
}
U8Vec4;

typedef union U16Vec2
{
    u16 values[2];

    struct { u16  x,  y; };
    struct { u16  r,  g; };
    struct { u16 v0, v1; };
}
U16Vec2;

typedef union U16Vec3
{
    u16 values[3];

    struct { U16Vec2 xy; u16 _1; };
    struct { u16 _2; U16Vec2 yz; };

    struct { u16  x,  y,  z; };
    struct { u16  r,  g,  b; };
    struct { u16 v0, v1, v2; };
}
U16Vec3;

typedef union U16Vec4
{
    u16 values[4];

    struct { U16Vec2 xy; U16Vec2 zw; };
    struct { u16 _1; U16Vec2 yz; u16 _2; };

    struct { U16Vec3 xyz; u16 _3; };
    struct { u16 _4; U16Vec3 yzw; };

    struct { u16  x,  y,  z,  w; };
    struct { u16  r,  g,  b,  a; };
    struct { u16 v0, v1, v2, v3; };
}
U16Vec4;

typedef union U32Vec2
{
    u32 values[2];

    struct { u32  x,  y; };
    struct { u32  r,  g; };
    struct { u32 v0, v1; };
}
U32Vec2;

typedef union U32Vec3
{
    u32 values[3];

    struct { U32Vec2 xy; u32 _1; };
    struct { u32 _2; U32Vec2 yz; };

    struct { u32  x,  y,  z; };
    struct { u32  r,  g,  b; };
    struct { u32 v0, v1, v2; };
}
U32Vec3;

typedef union U32Vec4
{
    u32 values[4];

    struct { U32Vec2 xy; U32Vec2 zw; };
    struct { u32 _1; U32Vec2 yz; u32 _2; };

    struct { U32Vec3 xyz; u32 _3; };
    struct { u32 _4; U32Vec3 yzw; };

    struct { u32  x,  y,  z,  w; };
    struct { u32  r,  g,  b,  a; };
    struct { u32 v0, v1, v2, v3; };
}
U32Vec4;

typedef union U64Vec2
{
    u64 values[2];

    struct { u64  x,  y; };
    struct { u64  r,  g; };
    struct { u64 v0, v1; };
}
U64Vec2;

typedef union U64Vec3
{
    u64 values[3];

    struct { U64Vec2 xy; u64 _1; };
    struct { u64 _2; U64Vec2 yz; };

    struct { u64  x,  y,  z; };
    struct { u64  r,  g,  b; };
    struct { u64 v0, v1, v2; };
}
U64Vec3;

typedef union U64Vec4
{
    u64 values[4];

    struct { U64Vec2 xy; U64Vec2 zw; };
    struct { u64 _1; U64Vec2 yz; u64 _2; };

    struct { U64Vec3 xyz; u64 _3; };
    struct { u64 _4; U64Vec3 yzw; };

    struct { u64  x,  y,  z,  w; };
    struct { u64  r,  g,  b,  a; };
    struct { u64 v0, v1, v2, v3; };
}
U64Vec4;

U8Vec2 u8Vec2(u8 v0, u8 v1);

U8Vec3 u8Vec3(u8 v0, u8 v1, u8 v2);

U8Vec4 u8Vec4(u8 v0, u8 v1, u8 v2, u8 v3);

U16Vec2 u16Vec2(u16 v0, u16 v1);

U16Vec3 u16Vec3(u16 v0, u16 v1, u16 v2);

U16Vec4 u16Vec4(u16 v0, u16 v1, u16 v2, u16 v3);

U32Vec2 u32Vec2(u32 v0, u32 v1);

U32Vec3 u32Vec3(u32 v0, u32 v1, u32 v2);

U32Vec4 u32Vec4(u32 v0, u32 v1, u32 v2, u32 v3);

U64Vec2 u64Vec2(u64 v0, u64 v1);

U64Vec3 u64Vec3(u64 v0, u64 v1, u64 v2);

U64Vec4 u64Vec4(u64 v0, u64 v1, u64 v2, u64 v3);

#endif // VECTOR_UNSIGNED_H
