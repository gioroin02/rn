#include "../../../src/rho-base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    RUint8 memory[32] = {0};

    for (RInt i = 0; i < sizeof memory; i += 1)
        memory[i] = 48 + (RUint8) i;

    for (RInt i = 0; i < sizeof memory; i += 1) {
        printf("%c", memory[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }

    rho_memory_shift_forw(memory, sizeof memory, 8, 32);

    printf("\n");

    for (RInt i = 0; i < sizeof memory; i += 1) {
        printf("%c", memory[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }

    rho_memory_shift_back(memory, sizeof memory, 8, 32);

    printf("\n");

    for (RInt i = 0; i < sizeof memory; i += 1) {
        printf("%c", memory[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }
}
