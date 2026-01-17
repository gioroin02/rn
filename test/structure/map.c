#include "../../src/string/export.h"
#include "../../src/structure/export.h"

#include <stdio.h>

typedef PMap(PString8, U32) PMapString8U32;

Int pString8Hash(PString8* key)
{
    Int result = 0;
    Int index  = 0;

    for (index = 0; index < key->size; index += 1)
        result += ((Int) key->values[index]);

    return result;
}

Bool pString8IsEqual(PString8* key, PString8* other)
{
    Int index = 0;

    if (key->size != other->size) return 0;

    for (index = 0; index < key->size; index += 1) {
        if (key->values[index] != other->values[index])
            return 0;
    }

    return 1;
}

void showPairs(PMapString8U32* self, PString8* keys, Int size)
{
    Int index = 0;

    for (index = 0; index < size; index += 1) {
        U32* value = pMapGetPntr(self, keys[index]);

        printf("map(%s) -> ", keys[index].values);

        if (value != 0)
            printf("%lu\n", *value);
        else
            printf("null\n");
    }
}

void showLists(PMapString8U32* self)
{
    Int index = 0;

    for (index = 0; index < pMapCount(self); index += 1) {
        PString8 key   = self->keys[index];
        U32      value = self->values[index];

        printf("map(%lli) -> %s, %lu\n",
            index, key.values, value);
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
