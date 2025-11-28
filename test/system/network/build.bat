@echo off

set "base=src\base\export.c"
set "base_memory=src\base\memory\export.c"
set "system_network=src\system\network\export.c"

set "test_address_ip=test\system\network\address-ip.c"

zig cc --std=c99 %base% %base_memory% %system_network% %test_address_ip% ^
    -o bin\system_network_address_ip.exe
