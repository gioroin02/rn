#ifndef VECTOR_FLOATING_H
#define VECTOR_FLOATING_H

#include "import.h"

#define f32v2(x, y)       ((F32Vec2) {(x), (y)})
#define f32v3(x, y, z)    ((F32Vec3) {(x), (y), (z)})
#define f32v4(x, y, z, w) ((F32Vec4) {(x), (y), (z), (w)})

#define f64v2(x, y)       ((F64Vec2) {(x), (y)})
#define f64v3(x, y, z)    ((F64Vec3) {(x), (y), (z)})
#define f64v4(x, y, z, w) ((F64Vec4) {(x), (y), (z), (w)})

typedef union F32Vec2
{
    F32 values[2];

    struct { F32  x,  y; };
    struct { F32  r,  g; };
    struct { F32 v0, v1; };
}
F32Vec2;

typedef union F32Vec3
{
    F32 values[3];

    struct { F32Vec2 xy; F32 _1; };
    struct { F32 _2; F32Vec2 yz; };

    struct { F32  x,  y,  z; };
    struct { F32  r,  g,  b; };
    struct { F32 v0, v1, v2; };
}
F32Vec3;

typedef union F32Vec4
{
    F32 values[4];

    struct { F32Vec2 xy; F32Vec2 zw; };
    struct { F32 _1; F32Vec2 yz; F32 _2; };

    struct { F32Vec3 xyz; F32 _3; };
    struct { F32 _4; F32Vec3 yzw; };

    struct { F32  x,  y,  z,  w; };
    struct { F32  r,  g,  b,  a; };
    struct { F32 v0, v1, v2, v3; };
}
F32Vec4;

typedef union F64Vec2
{
    F64 values[2];

    struct { F64  x,  y; };
    struct { F64  r,  g; };
    struct { F64 v0, v1; };
}
F64Vec2;

typedef union F64Vec3
{
    F64 values[3];

    struct { F64Vec2 xy; F64 _1; };
    struct { F64 _2; F64Vec2 yz; };

    struct { F64  x,  y,  z; };
    struct { F64  r,  g,  b; };
    struct { F64 v0, v1, v2; };
}
F64Vec3;

typedef union F64Vec4
{
    F64 values[4];

    struct { F64Vec2 xy; F64Vec2 zw; };
    struct { F64 _1; F64Vec2 yz; F64 _2; };

    struct { F64Vec3 xyz; F64 _3; };
    struct { F64 _4; F64Vec3 yzw; };

    struct { F64  x,  y,  z,  w; };
    struct { F64  r,  g,  b,  a; };
    struct { F64 v0, v1, v2, v3; };
}
F64Vec4;

#endif // VECTOR_FLOATING_H
