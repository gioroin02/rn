#include "../../src/base/string/export.h"
#include "../../src/structure/export.h"

#include <stdio.h>

typedef RMap(RString8, RUint32) RString8Uint32Map;

RInt rho_string8_hash(RString8* key)
{
    RInt result = 0;

    for (RInt i = 0; i < key->size; i += 1)
        result += ((RInt) key->values[i]);

    return result;
}

RBool32 rho_string8_is_equal(RString8* key, RString8* other)
{
    if (key->size != other->size) return 0;

    for (RInt i = 0; i < key->size; i += 1) {
        if (key->values[i] != other->values[i])
            return 0;
    }

    return 1;
}

void show_pairs(RString8Uint32Map* self, RString8* keys, RInt size)
{
    for (RInt i = 0; i < size; i += 1) {
        RUint32* value = rho_map_get_pntr(self, keys[i]);

        printf("map(%s) -> ", keys[i].values);

        if (value != 0)
            printf("%lu\n", *value);
        else
            printf("null\n");
    }
}

void show_lists(RString8Uint32Map* self)
{
    for (RInt i = 0; i < rho_map_count(self); i += 1) {
        RString8 key   = self->keys[i];
        RUint32  value = self->values[i];

        printf("map(%lli) -> %s, %lu\n",
            i, key.values, value);
    }
}

int main(int argc, char** argv)
{
    RUint8 memory[RHO_MEMORY_KIB] = {0};

    RMemoryArena arena = rho_memory_arena_make(memory, sizeof memory);

    RString8Uint32Map map = {0};

    rho_map_create(&map, &arena, 16, &rho_string8_hash, &rho_string8_is_equal);

    RString8 keys[3] = {
        rho_string8("Filiberto"),
        rho_string8("Astronfo"),
        rho_string8("Roboldofo"),
    };

    rho_map_insert(&map, keys[0], 10);
    rho_map_insert(&map, keys[1], 20);
    rho_map_insert(&map, keys[2], 30);

    printf("Pairs: {\n");
        show_pairs(&map, keys, 3);
    printf("}\n");

    printf("Lists: {\n");
        show_lists(&map);
    printf("}\n");

    rho_map_clear(&map);

    printf("\n");

    printf("Pairs: {\n");
        show_pairs(&map, keys, 3);
    printf("}\n");

    printf("Lists: {\n");
        show_lists(&map);
    printf("}\n");

    rho_map_destroy(&map);
}
