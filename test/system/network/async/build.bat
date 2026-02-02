@echo off

set "compiler=zig cc"

set "impl=%impl% src\rho-base\export.c"
set "impl=%impl% src\rho-base\memory\export.c"
set "impl=%impl% src\rho-system\memory\export.c"
set "impl=%impl% src\rho-system\asyncio\export.c"
set "impl=%impl% src\rho-system\network\export.c"
set "impl=%impl% src\rho-system\network\async\export.c"

set "test_server_tcp=test\system\network\async\server-tcp.c"
set "test_client_tcp=test\system\network\async\client-tcp.c"

%compiler% --std=c99 %impl% %test_server_tcp% -lws2_32 -o bin\system_network_async_server_tcp.exe
%compiler% --std=c99 %impl% %test_client_tcp% -lws2_32 -o bin\system_network_async_client_tcp.exe
