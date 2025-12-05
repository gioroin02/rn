@echo off

set "compiler=zig cc --std=c99"

set "base=src\base\export.c"
set "base_memory=src\base\memory\export.c"
set "system_memory=src\system\memory\export.c"
set "system_network=src\system\network\export.c"
set "system_asyncio=src\system\asyncio\export.c"

set "test_server_tcp=test\system\asyncio\server-tcp.c"
set "test_client_tcp=test\system\asyncio\client-tcp.c"

%compiler% %base% %base_memory% %system_memory% %system_network% %system_asyncio% %test_server_tcp% ^
    -lws2_32 -o bin\system_asyncio_server_tcp.exe

%compiler% %base% %base_memory% %system_memory% %system_network% %system_asyncio% %test_client_tcp% ^
    -lws2_32 -o bin\system_asyncio_client_tcp.exe
