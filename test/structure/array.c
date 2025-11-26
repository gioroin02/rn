#include "../../src/structure/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    u32 memory[16] = {0};

    struct { u32* values; RN_ARRAY_TAG; } array =
        {.values = memory, .size = 16};

    ssize count = 0;

    count = rnArrayInsert(&array, count, 156);
    count = rnArrayInsert(&array, count, 222);
    count = rnArrayInsert(&array, count, 9);

    for (ssize i = 0; i < array.count; i += 1)
        printf("#%03lli %lu\n", i, array.values[i]);
}
