#include "../../../src/base/export.h"
#include "../../../src/base/memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    u32 memory[16] = {0};

    RnMemorySlice slice = rnSliceCut(memory, -1, 555);

    for (ssize i = 0; i < slice.size; i += 1) {
        printf("#%03lli ", i + 1);

        for (ssize j = 0; j < slice.step; j += 1)
            printf("%3u ", slice.values[i + j]);

        printf("\n");
    }
}
