#ifndef VECTOR_FLOATING_H
#define VECTOR_FLOATING_H

#include "import.h"

typedef union F32Vec2
{
    f32 values[2];

    struct { f32  x,  y; };
    struct { f32  r,  g; };
    struct { f32 v0, v1; };
}
F32Vec2;

typedef union F32Vec3
{
    f32 values[3];

    struct { F32Vec2 xy; f32 _1; };
    struct { f32 _2; F32Vec2 yz; };

    struct { f32  x,  y,  z; };
    struct { f32  r,  g,  b; };
    struct { f32 v0, v1, v2; };
}
F32Vec3;

typedef union F32Vec4
{
    f32 values[4];

    struct { F32Vec2 xy; F32Vec2 zw; };
    struct { f32 _1; F32Vec2 yz; f32 _2; };

    struct { F32Vec3 xyz; f32 _3; };
    struct { f32 _4; F32Vec3 yzw; };

    struct { f32  x,  y,  z,  w; };
    struct { f32  r,  g,  b,  a; };
    struct { f32 v0, v1, v2, v3; };
}
F32Vec4;

typedef union F64Vec2
{
    f64 values[2];

    struct { f64  x,  y; };
    struct { f64  r,  g; };
    struct { f64 v0, v1; };
}
F64Vec2;

typedef union F64Vec3
{
    f64 values[3];

    struct { F64Vec2 xy; f64 _1; };
    struct { f64 _2; F64Vec2 yz; };

    struct { f64  x,  y,  z; };
    struct { f64  r,  g,  b; };
    struct { f64 v0, v1, v2; };
}
F64Vec3;

typedef union F64Vec4
{
    f64 values[4];

    struct { F64Vec2 xy; F64Vec2 zw; };
    struct { f64 _1; F64Vec2 yz; f64 _2; };

    struct { F64Vec3 xyz; f64 _3; };
    struct { f64 _4; F64Vec3 yzw; };

    struct { f64  x,  y,  z,  w; };
    struct { f64  r,  g,  b,  a; };
    struct { f64 v0, v1, v2, v3; };
}
F64Vec4;

F32Vec2 f32Vec2(f32 v0, f32 v1);

F32Vec3 f32Vec3(f32 v0, f32 v1, f32 v2);

F32Vec4 f32Vec4(f32 v0, f32 v1, f32 v2, f32 v3);

F64Vec2 f64Vec2(f64 v0, f64 v1);

F64Vec3 f64Vec3(f64 v0, f64 v1, f64 v2);

F64Vec4 f64Vec4(f64 v0, f64 v1, f64 v2, f64 v3);

#endif // VECTOR_FLOATING_H
