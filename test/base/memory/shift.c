#include "../../../src/base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    U8 memory[32] = {0};

    for (Int i = 0; i < sizeof memory; i += 1)
        memory[i] = (U8) i;

    for (Int i = 0; i < sizeof memory; i += 1) {
        printf("%2X ", memory[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }

    pMemoryShiftForw(memory, sizeof memory, 8, 0xAB);

    printf("\n");

    for (Int i = 0; i < sizeof memory; i += 1) {
        printf("%2X ", memory[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }

    pMemoryShiftBack(memory, sizeof memory, 8, 0xAB);

    printf("\n");

    for (Int i = 0; i < sizeof memory; i += 1) {
        printf("%2X ", memory[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }
}
