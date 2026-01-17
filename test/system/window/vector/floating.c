#ifndef VECTOR_FLOATING_C
#define VECTOR_FLOATING_C

#include "floating.h"

F32Vec2 f32Vec2(f32 v0, f32 v1)
{
    F32Vec2 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

F32Vec3 f32Vec3(f32 v0, f32 v1, f32 v2)
{
    F32Vec3 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

F32Vec4 f32Vec4(f32 v0, f32 v1, f32 v2, f32 v3)
{
    F32Vec4 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

F64Vec2 f64Vec2(f64 v0, f64 v1)
{
    F64Vec2 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

F64Vec3 f64Vec3(f64 v0, f64 v1, f64 v2)
{
    F64Vec3 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;

    return result;
}

F64Vec4 f64Vec4(f64 v0, f64 v1, f64 v2, f64 v3)
{
    F64Vec4 result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

#endif // VECTOR_FLOATING_C
