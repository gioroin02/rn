@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\system\memory\export.c"
set "impl=%impl% src\system\network\export.c"

set "test_address_ip=test\system\network\address-ip.c"
set "test_server_udp=test\system\network\server-udp.c"
set "test_client_udp=test\system\network\client-udp.c"
set "test_server_tcp=test\system\network\server-tcp.c"
set "test_client_tcp=test\system\network\client-tcp.c"

%compiler% --std=c99 %impl% %test_address_ip% -lws2_32 -o bin\system_network_address_ip.exe
%compiler% --std=c99 %impl% %test_server_udp% -lws2_32 -o bin\system_network_server_udp.exe
%compiler% --std=c99 %impl% %test_client_udp% -lws2_32 -o bin\system_network_client_udp.exe
%compiler% --std=c99 %impl% %test_server_tcp% -lws2_32 -o bin\system_network_server_tcp.exe
%compiler% --std=c99 %impl% %test_client_tcp% -lws2_32 -o bin\system_network_client_tcp.exe
