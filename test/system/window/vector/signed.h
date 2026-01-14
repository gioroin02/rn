#ifndef VECTOR_SIGNED_H
#define VECTOR_SIGNED_H

#include "import.h"

typedef union S8Vec2
{
    s8 values[2];

    struct { s8  x,  y; };
    struct { s8  r,  g; };
    struct { s8 v0, v1; };
}
S8Vec2;

typedef union S8Vec3
{
    s8 values[3];

    struct { S8Vec2 xy; s8 _1; };
    struct { s8 _2; S8Vec2 yz; };

    struct { s8  x,  y,  z; };
    struct { s8  r,  g,  b; };
    struct { s8 v0, v1, v2; };
}
S8Vec3;

typedef union S8Vec4
{
    s8 values[4];

    struct { S8Vec2 xy; S8Vec2 zw; };
    struct { s8 _1; S8Vec2 yz; s8 _2; };

    struct { S8Vec3 xyz; s8 _3; };
    struct { s8 _4; S8Vec3 yzw; };

    struct { s8  x,  y,  z,  w; };
    struct { s8  r,  g,  b,  a; };
    struct { s8 v0, v1, v2, v3; };
}
S8Vec4;

typedef union S16Vec2
{
    s16 values[2];

    struct { s16  x,  y; };
    struct { s16  r,  g; };
    struct { s16 v0, v1; };
}
S16Vec2;

typedef union S16Vec3
{
    s16 values[3];

    struct { S16Vec2 xy; s16 _1; };
    struct { s16 _2; S16Vec2 yz; };

    struct { s16  x,  y,  z; };
    struct { s16  r,  g,  b; };
    struct { s16 v0, v1, v2; };
}
S16Vec3;

typedef union S16Vec4
{
    s16 values[4];

    struct { S16Vec2 xy; S16Vec2 zw; };
    struct { s16 _1; S16Vec2 yz; s16 _2; };

    struct { S16Vec3 xyz; s16 _3; };
    struct { s16 _4; S16Vec3 yzw; };

    struct { s16  x,  y,  z,  w; };
    struct { s16  r,  g,  b,  a; };
    struct { s16 v0, v1, v2, v3; };
}
S16Vec4;

typedef union S32Vec2
{
    s32 values[2];

    struct { s32  x,  y; };
    struct { s32  r,  g; };
    struct { s32 v0, v1; };
}
S32Vec2;

typedef union S32Vec3
{
    s32 values[3];

    struct { S32Vec2 xy; s32 _1; };
    struct { s32 _2; S32Vec2 yz; };

    struct { s32  x,  y,  z; };
    struct { s32  r,  g,  b; };
    struct { s32 v0, v1, v2; };
}
S32Vec3;

typedef union S32Vec4
{
    s32 values[4];

    struct { S32Vec2 xy; S32Vec2 zw; };
    struct { s32 _1; S32Vec2 yz; s32 _2; };

    struct { S32Vec3 xyz; s32 _3; };
    struct { s32 _4; S32Vec3 yzw; };

    struct { s32  x,  y,  z,  w; };
    struct { s32  r,  g,  b,  a; };
    struct { s32 v0, v1, v2, v3; };
}
S32Vec4;

typedef union S64Vec2
{
    s64 values[2];

    struct { s64  x,  y; };
    struct { s64  r,  g; };
    struct { s64 v0, v1; };
}
S64Vec2;

typedef union S64Vec3
{
    s64 values[3];

    struct { S64Vec2 xy; s64 _1; };
    struct { s64 _2; S64Vec2 yz; };

    struct { s64  x,  y,  z; };
    struct { s64  r,  g,  b; };
    struct { s64 v0, v1, v2; };
}
S64Vec3;

typedef union S64Vec4
{
    s64 values[4];

    struct { S64Vec2 xy; S64Vec2 zw; };
    struct { s64 _1; S64Vec2 yz; s64 _2; };

    struct { S64Vec3 xyz; s64 _3; };
    struct { s64 _4; S64Vec3 yzw; };

    struct { s64  x,  y,  z,  w; };
    struct { s64  r,  g,  b,  a; };
    struct { s64 v0, v1, v2, v3; };
}
S64Vec4;

S8Vec2 s8Vec2(s8 v0, s8 v1);

S8Vec3 s8Vec3(s8 v0, s8 v1, s8 v2);

S8Vec4 s8Vec4(s8 v0, s8 v1, s8 v2, s8 v3);

S16Vec2 s16Vec2(s16 v0, s16 v1);

S16Vec3 s16Vec3(s16 v0, s16 v1, s16 v2);

S16Vec4 s16Vec4(s16 v0, s16 v1, s16 v2, s16 v3);

S32Vec2 s32Vec2(s32 v0, s32 v1);

S32Vec3 s32Vec3(s32 v0, s32 v1, s32 v2);

S32Vec4 s32Vec4(s32 v0, s32 v1, s32 v2, s32 v3);

S64Vec2 s64Vec2(s64 v0, s64 v1);

s64 s64Vec2Cross(S64Vec2 self, S64Vec2 other);

S64Vec3 s64Vec3(s64 v0, s64 v1, s64 v2);

S64Vec4 s64Vec4(s64 v0, s64 v1, s64 v2, s64 v3);

#endif // VECTOR_SIGNED_H
