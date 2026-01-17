#ifndef VECTOR_UNSIGNED_C
#define VECTOR_UNSIGNED_C

#include "unsigned.h"

U8Vec2 u8Vec2(u8 v0, u8 v1)
{
    U8Vec2 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

U8Vec3 u8Vec3(u8 v0, u8 v1, u8 v2)
{
    U8Vec3 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

U8Vec4 u8Vec4(u8 v0, u8 v1, u8 v2, u8 v3)
{
    U8Vec4 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

U16Vec2 u16Vec2(u16 v0, u16 v1)
{
    U16Vec2 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

U16Vec3 u16Vec3(u16 v0, u16 v1, u16 v2)
{
    U16Vec3 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

U16Vec4 u16Vec4(u16 v0, u16 v1, u16 v2, u16 v3)
{
    U16Vec4 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

U32Vec2 u32Vec2(u32 v0, u32 v1)
{
    U32Vec2 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

U32Vec3 u32Vec3(u32 v0, u32 v1, u32 v2)
{
    U32Vec3 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

U32Vec4 u32Vec4(u32 v0, u32 v1, u32 v2, u32 v3)
{
    U32Vec4 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

U64Vec2 u64Vec2(u64 v0, u64 v1)
{
    U64Vec2 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

U64Vec3 u64Vec3(u64 v0, u64 v1, u64 v2)
{
    U64Vec3 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

U64Vec4 u64Vec4(u64 v0, u64 v1, u64 v2, u64 v3)
{
    U64Vec4 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

#endif // VECTOR_UNSIGNED_C
