#ifndef RHO_BASE_TYPE_H
#define RHO_BASE_TYPE_H

#include "define.h"
#include "system.h"

typedef unsigned char      RUint8;
typedef unsigned short     RUint16;
typedef unsigned long      RUint32;
typedef unsigned long long RUint64;

#define RHO_UINT8_MAX  ((RUint8)  0xFFu)
#define RHO_UINT16_MAX ((RUint16) 0xFFFFu)
#define RHO_UINT32_MAX ((RUint32) 0xFFFFFFFFlu)
#define RHO_UINT64_MAX ((RUint64) 0xFFFFFFFFFFFFFFFFllu)

#define RHO_UINT8_MIN  ((RUint8)  0u)
#define RHO_UINT16_MIN ((RUint16) 0u)
#define RHO_UINT32_MIN ((RUint32) 0lu)
#define RHO_UINT64_MIN ((RUint64) 0llu)

typedef signed char      RInt8;
typedef signed short     RInt16;
typedef signed long      RInt32;
typedef signed long long RInt64;

#define RHO_INT8_MAX  ((RInt8)  0x7F)
#define RHO_INT16_MAX ((RInt16) 0x7FFF)
#define RHO_INT32_MAX ((RInt32) 0x7FFFFFFFl)
#define RHO_INT64_MAX ((RInt64) 0x7FFFFFFFFFFFFFFFll)

#define RHO_INT8_MIN  ((RInt8)  0x80)
#define RHO_INT16_MIN ((RInt16) 0x8000)
#define RHO_INT32_MIN ((RInt32) 0x80000000l)
#define RHO_INT64_MIN ((RInt64) 0x8000000000000000ll)

typedef RUint8  RBool8;
typedef RUint16 RBool16;
typedef RUint32 RBool32;
typedef RUint64 RBool64;

typedef float  RFloat32;
typedef double RFloat64;

#define RHO_FLOAT32_NAN (- ((RFloat32) 0.0 / (RFloat32) 0.0))
#define RHO_FLOAT64_NAN (- ((RFloat64) 0.0 / (RFloat64) 0.0))

typedef char  RChar8;
typedef short RChar16;
typedef long  RChar32;

typedef long RChar;

#if RHO_WORD == RHO_WORD_64

    typedef RUint64  RUint;
    typedef RInt64   RInt;
    typedef RFloat64 RFloat;

    #define RHO_UINT_MAX RHO_UINT64_MAX
    #define RHO_UINT_MIN RHO_UINT64_MIN

    #define RHO_INT_MAX RHO_INT64_MAX
    #define RHO_INT_MIN RHO_INT64_MIN

    #define RHO_FLOAT_NAN RHO_FLOAT64_NAN

#elif RHO_WORD == RHO_WORD_32

    typedef RUint32  RUint;
    typedef Rint32   Rint;
    typedef RFloat32 RFloat;

    #define RHO_UINT_MAX RHO_UINT32_MAX
    #define RHO_UINT_MIN RHO_UINT32_MIN

    #define RHO_INT_MAX RHO_INT32_MAX
    #define RHO_INT_MIN RHO_INT32_MIN

    #define RHO_FLOAT_NAN RHO_FLOAT32_NAN

#else

    typedef RUint16 RUint;
    typedef Rint16  Rint;

    #define RHO_UINT_MAX RHO_UINT16_MAX
    #define RHO_UINT_MIN RHO_UINT16_MIN

    #define RHO_INT_MAX RHO_INT16_MAX
    #define RHO_INT_MIN RHO_INT16_MIN

#endif

#endif
