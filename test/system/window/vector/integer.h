#ifndef VECTOR_INTEGER_H
#define VECTOR_INTEGER_H

#include "import.h"

#define i8v2(x, y)       ((I8Vec2) {(x), (y)})
#define i8v3(x, y, z)    ((I8Vec3) {(x), (y), (z)})
#define i8v4(x, y, z, w) ((I8Vec4) {(x), (y), (z), (w)})

#define i16v2(x, y)       ((I16Vec2) {(x), (y)})
#define i16v3(x, y, z)    ((I16Vec3) {(x), (y), (z)})
#define i16v4(x, y, z, w) ((I16Vec4) {(x), (y), (z), (w)})

#define i32v2(x, y)       ((I32Vec2) {(x), (y)})
#define i32v3(x, y, z)    ((I32Vec3) {(x), (y), (z)})
#define i32v4(x, y, z, w) ((I32Vec4) {(x), (y), (z), (w)})

#define i64v2(x, y)       ((I64Vec2) {(x), (y)})
#define i64v3(x, y, z)    ((I64Vec3) {(x), (y), (z)})
#define i64v4(x, y, z, w) ((I64Vec4) {(x), (y), (z), (w)})

typedef union I8Vec2
{
    I8 values[2];

    struct { I8  x,  y; };
    struct { I8  r,  g; };
    struct { I8 v0, v1; };
}
I8Vec2;

typedef union I8Vec3
{
    I8 values[3];

    struct { I8Vec2 xy; I8 _1; };
    struct { I8 _2; I8Vec2 yz; };

    struct { I8  x,  y,  z; };
    struct { I8  r,  g,  b; };
    struct { I8 v0, v1, v2; };
}
I8Vec3;

typedef union I8Vec4
{
    I8 values[4];

    struct { I8Vec2 xy; I8Vec2 zw; };
    struct { I8 _1; I8Vec2 yz; I8 _2; };

    struct { I8Vec3 xyz; I8 _3; };
    struct { I8 _4; I8Vec3 yzw; };

    struct { I8  x,  y,  z,  w; };
    struct { I8  r,  g,  b,  a; };
    struct { I8 v0, v1, v2, v3; };
}
I8Vec4;

typedef union S16Vec2
{
    I16 values[2];

    struct { I16  x,  y; };
    struct { I16  r,  g; };
    struct { I16 v0, v1; };
}
S16Vec2;

typedef union S16Vec3
{
    I16 values[3];

    struct { S16Vec2 xy; I16 _1; };
    struct { I16 _2; S16Vec2 yz; };

    struct { I16  x,  y,  z; };
    struct { I16  r,  g,  b; };
    struct { I16 v0, v1, v2; };
}
S16Vec3;

typedef union S16Vec4
{
    I16 values[4];

    struct { S16Vec2 xy; S16Vec2 zw; };
    struct { I16 _1; S16Vec2 yz; I16 _2; };

    struct { S16Vec3 xyz; I16 _3; };
    struct { I16 _4; S16Vec3 yzw; };

    struct { I16  x,  y,  z,  w; };
    struct { I16  r,  g,  b,  a; };
    struct { I16 v0, v1, v2, v3; };
}
S16Vec4;

typedef union I16Vec2
{
    I32 values[2];

    struct { I32  x,  y; };
    struct { I32  r,  g; };
    struct { I32 v0, v1; };
}
I16Vec2;

typedef union I16Vec3
{
    I32 values[3];

    struct { I16Vec2 xy; I32 _1; };
    struct { I32 _2; I16Vec2 yz; };

    struct { I32  x,  y,  z; };
    struct { I32  r,  g,  b; };
    struct { I32 v0, v1, v2; };
}
I16Vec3;

typedef union I16Vec4
{
    I32 values[4];

    struct { I16Vec2 xy; I16Vec2 zw; };
    struct { I32 _1; I16Vec2 yz; I32 _2; };

    struct { I16Vec3 xyz; I32 _3; };
    struct { I32 _4; I16Vec3 yzw; };

    struct { I32  x,  y,  z,  w; };
    struct { I32  r,  g,  b,  a; };
    struct { I32 v0, v1, v2, v3; };
}
I16Vec4;

typedef union I64Vec2
{
    I64 values[2];

    struct { I64  x,  y; };
    struct { I64  r,  g; };
    struct { I64 v0, v1; };
}
I64Vec2;

typedef union I64Vec3
{
    I64 values[3];

    struct { I64Vec2 xy; I64 _1; };
    struct { I64 _2; I64Vec2 yz; };

    struct { I64  x,  y,  z; };
    struct { I64  r,  g,  b; };
    struct { I64 v0, v1, v2; };
}
I64Vec3;

typedef union I64Vec4
{
    I64 values[4];

    struct { I64Vec2 xy; I64Vec2 zw; };
    struct { I64 _1; I64Vec2 yz; I64 _2; };

    struct { I64Vec3 xyz; I64 _3; };
    struct { I64 _4; I64Vec3 yzw; };

    struct { I64  x,  y,  z,  w; };
    struct { I64  r,  g,  b,  a; };
    struct { I64 v0, v1, v2, v3; };
}
I64Vec4;

#endif // VECTOR_INTEGER_H
