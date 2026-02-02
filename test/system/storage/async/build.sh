compiler="gcc --debug"

impl="$impl src/rho-base/export.c"
impl="$impl src/rho-base/memory/export.c"
impl="$impl src/rho-base/string/export.c"
impl="$impl src/rho-system/memory/export.c"
impl="$impl src/rho-system/asyncio/export.c"
impl="$impl src/rho-system/storage/export.c"
impl="$impl src/rho-system/storage/async/export.c"

test_reading="test/system/storage/async/reading.c"

$compiler --std=c99 $impl $test_reading -o bin/system_storage_async_reading.exe
