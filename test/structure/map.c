#include "../../src/base/string/export.h"
#include "../../src/structure/export.h"

#include <stdio.h>

typedef PMap(PString8, U32) PMapString8U32;

Int pString8Hash(PString8* key)
{
    Int result = 0;

    for (Int i = 0; i < key->size; i += 1)
        result += ((Int) key->values[i]);

    return result;
}

B32 pString8IsEqual(PString8* key, PString8* other)
{
    if (key->size != other->size) return 0;

    for (Int i = 0; i < key->size; i += 1) {
        if (key->values[i] != other->values[i])
            return 0;
    }

    return 1;
}

void showPairs(PMapString8U32* self, PString8* keys, Int size)
{
    for (Int i = 0; i < size; i += 1) {
        U32* value = pMapGetPntr(self, keys[i]);

        printf("map(%s) -> ", keys[i].values);

        if (value != 0)
            printf("%lu\n", *value);
        else
            printf("null\n");
    }
}

void showLists(PMapString8U32* self)
{
    for (Int i = 0; i < pMapCount(self); i += 1) {
        PString8 key   = self->keys[i];
        U32      value = self->values[i];

        printf("map(%lli) -> %s, %lu\n",
            i, key.values, value);
    }
}

int main(int argc, char** argv)
{
    U8 memory[1024];

    PMemoryArena arena = pMemoryArenaMake(memory, sizeof memory);

    PMapString8U32 map;

    pMapCreate(&map, &arena, 16, &pString8Hash, &pString8IsEqual);

    PString8 keys[3] = {
        pString8("Filiberto"),
        pString8("Astronfo"),
        pString8("Roboldofo"),
    };

    pMapInsert(&map, keys[0], 10);
    pMapInsert(&map, keys[1], 20);
    pMapInsert(&map, keys[2], 30);

    showPairs(&map, keys, 3);
    showLists(&map);

    pMapClear(&map);

    printf("\n");

    showPairs(&map, keys, 3);
    showLists(&map);
}
