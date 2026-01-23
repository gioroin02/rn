compiler="gcc -Wno-endif-labels"

impl="$impl src/base/export.c"
impl="$impl src/base/memory/export.c"
impl="$impl src/system/memory/export.c"

test_arena="test/system/memory/arena.c"

$compiler --std=c89 $impl $test_arena -o bin/system_memory_arena.exe
