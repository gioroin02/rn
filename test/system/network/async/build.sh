compiler="gcc"

impl="$impl src/base/export.c"
impl="$impl src/base/memory/export.c"
impl="$impl src/system/memory/export.c"
impl="$impl src/system/asyncio/export.c"
impl="$impl src/system/network/export.c"
impl="$impl src/system/network/async/export.c"

test_server_tcp="test/system/network/async/server-tcp.c"
test_client_tcp="test/system/network/async/client-tcp.c"

$compiler --std=c89 $impl $test_server_tcp -o bin/system_network_async_server_tcp.exe
$compiler --std=c89 $impl $test_client_tcp -o bin/system_network_async_client_tcp.exe
