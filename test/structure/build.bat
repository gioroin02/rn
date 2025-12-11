@echo off

set "compiler=zig cc"

set "base=src\base\export.c"
set "base_memory=src\base\memory\export.c"
set "structure=src\structure\export.c"

set "impl=%base% %base_memory% %structure%"

set "test_array=test\structure\array.c"
set "test_map=test\structure\map.c"

%compiler% --std=c99 %impl% %test_array% -o bin\structure_array.exe
%compiler% --std=c99 %impl% %test_map%   -o bin\structure_map.exe
