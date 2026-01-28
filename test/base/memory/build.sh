compiler="gcc --debug"

impl="$impl src/base/export.c"
impl="$impl src/base/memory/export.c"

test_order="test/base/memory/order.c"
test_arena="test/base/memory/arena.c"
test_pool="test/base/memory/pool.c"
test_shift="test/base/memory/shift.c"

$compiler --std=c99 $impl $test_order -o bin/base_memory_order.exe
$compiler --std=c99 $impl $test_arena -o bin/base_memory_arena.exe
$compiler --std=c99 $impl $test_pool  -o bin/base_memory_pool.exe
$compiler --std=c99 $impl $test_shift -o bin/base_memory_shift.exe
