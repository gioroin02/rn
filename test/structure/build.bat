@echo off

set "base=src\base\export.c"
set "base_memory=src\base\memory\export.c"
set "structure=src\structure\export.c"

set "test_array=test\structure\array.c"

zig cc --std=c99 %base% %base_memory% %structure% %test_array% ^
    -o bin\structure_array.exe
