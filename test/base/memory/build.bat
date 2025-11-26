@echo off

set "base=src\base\export.c"
set "base_memory=src\base\memory\export.c"

set "test_slice=test\base\memory\slice.c"

zig cc --std=c99 %base% %base_memory% %test_slice% -o bin\base_memory_slice.exe
