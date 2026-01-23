compiler="gcc -Wno-endif-labels"

impl="$impl src/base/export.c"
impl="$impl src/base/memory/export.c"
impl="$impl src/system/memory/export.c"
impl="$impl src/system/network/export.c"

test_address_ip="test/system/network/address-ip.c"
test_server_udp="test/system/network/server-udp.c"
test_client_udp="test/system/network/client-udp.c"
test_server_tcp="test/system/network/server-tcp.c"
test_client_tcp="test/system/network/client-tcp.c"

$compiler --std=c89 $impl $test_address_ip -o bin/system_network_address_ip.exe
$compiler --std=c89 $impl $test_server_udp -o bin/system_network_server_udp.exe
$compiler --std=c89 $impl $test_client_udp -o bin/system_network_client_udp.exe
$compiler --std=c89 $impl $test_server_tcp -o bin/system_network_server_tcp.exe
$compiler --std=c89 $impl $test_client_tcp -o bin/system_network_client_tcp.exe
