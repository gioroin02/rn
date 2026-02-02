compiler="gcc --debug"

impl="$impl src/rho-base/export.c"
impl="$impl src/rho-base/memory/export.c"
impl="$impl src/rho-system/memory/export.c"

test_arena="test/system/memory/arena.c"

$compiler --std=c99 $impl $test_arena -o bin/system_memory_arena.exe
