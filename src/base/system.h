#ifndef RHO_BASE_SYSTEM_H
#define RHO_BASE_SYSTEM_H

#ifndef NULL

    #define NULL ((void*) 0)

#endif

#define RHO_WORD_NONE  0
#define RHO_WORD_32    1
#define RHO_WORD_64    2
#define RHO_WORD_COUNT 3

#ifndef RHO_WORD

    #if defined(_WIN64)     || \
        defined(__PL64__)   || \
        defined(__x86_64__) || \
        defined(__amd64__)  || \
        defined(__aarch64__)

        #define RHO_WORD RHO_WORD_64

    #elif defined(_WIN32)    || \
          defined(__ILP32__) || \
          defined(_i386_)

        #define RHO_WORD RHO_WORD_32

    #else

        #define RHO_WORD RHO_WORD_NONE

    #endif

#endif

#define RHO_SYSTEM_NONE    0
#define RHO_SYSTEM_WINDOWS 1
#define RHO_SYSTEM_LINUX   2
#define RHO_SYSTEM_COUNT   3

#ifndef RHO_SYSTEM

    #if defined(_WIN32) || \
        defined(_WIN64)

        #define RHO_SYSTEM RHO_SYSTEM_WINDOWS

    #elif defined(__linux__)

        #define RHO_SYSTEM RHO_SYSTEM_LINUX

    #else

        #define RHO_SYSTEM RHO_SYSTEM_NONE

    #endif

#endif

#endif
