#ifndef VECTOR_SIGNED_C
#define VECTOR_SIGNED_C

#include "signed.h"

S8Vec2 s8Vec2(s8 v0, s8 v1)
{
    S8Vec2 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

S8Vec3 s8Vec3(s8 v0, s8 v1, s8 v2)
{
    S8Vec3 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

S8Vec4 s8Vec4(s8 v0, s8 v1, s8 v2, s8 v3)
{
    S8Vec4 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

S16Vec2 s16Vec2(s16 v0, s16 v1)
{
    S16Vec2 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

S16Vec3 s16Vec3(s16 v0, s16 v1, s16 v2)
{
    S16Vec3 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

S16Vec4 s16Vec4(s16 v0, s16 v1, s16 v2, s16 v3)
{
    S16Vec4 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

S32Vec2 s32Vec2(s32 v0, s32 v1)
{
    S32Vec2 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

S32Vec3 s32Vec3(s32 v0, s32 v1, s32 v2)
{
    S32Vec3 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

S32Vec4 s32Vec4(s32 v0, s32 v1, s32 v2, s32 v3)
{
    S32Vec4 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

S64Vec2 s64Vec2(s64 v0, s64 v1)
{
    S64Vec2 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

s64 s64Vec2Cross(S64Vec2 self, S64Vec2 other)
{
    return 0;
}

S64Vec3 s64Vec3(s64 v0, s64 v1, s64 v2)
{
    S64Vec3 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

S64Vec4 s64Vec4(s64 v0, s64 v1, s64 v2, s64 v3)
{
    S64Vec4 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

#endif // VECTOR_SIGNED_C
