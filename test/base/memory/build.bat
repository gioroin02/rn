@echo off

set "base=src\base\export.c"
set "base_memory=src\base\memory\export.c"

set "test_slice=test\base\memory\slice.c"
set "test_order=test\base\memory\order.c"

zig cc --std=c99 %base% %base_memory% %test_slice% ^
    -o bin\base_memory_slice.exe

zig cc --std=c99 %base% %base_memory% %test_order% ^
    -o bin\base_memory_order.exe
