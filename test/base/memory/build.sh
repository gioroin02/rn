compiler="gcc --debug"

impl="$impl src/rho-base/export.c"
impl="$impl src/rho-base/memory/export.c"

test_order="test/base/memory/order.c"
test_arena="test/base/memory/arena.c"
test_pool="test/base/memory/pool.c"

$compiler --std=c99 $impl $test_order -o bin/base_memory_order.exe
$compiler --std=c99 $impl $test_arena -o bin/base_memory_arena.exe
$compiler --std=c99 $impl $test_pool  -o bin/base_memory_pool.exe
