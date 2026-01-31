#include "../../../src/base/memory/export.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    if (rho_host_byte_order_is_network() != 0)
        printf("network\n");
    else
        printf("reverse\n");
}
