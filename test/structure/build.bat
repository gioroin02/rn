@echo off

set "compiler=zig cc"

set "impl=%impl% src\base\export.c"
set "impl=%impl% src\base\memory\export.c"
set "impl=%impl% src\string\export.c"
set "impl=%impl% src\structure\export.c"

set "test_array=test\structure\array.c"
set "test_map=test\structure\map.c"

%compiler% --std=c89 %impl% %test_array% -o bin\structure_array.exe
%compiler% --std=c89 %impl% %test_map%   -o bin\structure_map.exe
