compiler="gcc --debug"

impl="$impl src/rho-base/export.c"
impl="$impl src/rho-base/memory/export.c"
impl="$impl src/rho-system/memory/export.c"
impl="$impl src/rho-system/asyncio/export.c"
impl="$impl src/rho-system/network/export.c"
impl="$impl src/rho-system/network/async/export.c"

test_server_tcp="test/system/network/async/server-tcp.c"
test_client_tcp="test/system/network/async/client-tcp.c"

$compiler --std=c99 $impl $test_server_tcp -o bin/system_network_async_server_tcp.exe
$compiler --std=c99 $impl $test_client_tcp -o bin/system_network_async_client_tcp.exe
