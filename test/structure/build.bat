@echo off

set "compiler=zig cc"

set "impl=%impl% src\rho-base\export.c"
set "impl=%impl% src\rho-base\memory\export.c"
set "impl=%impl% src\rho-base\string\export.c"
set "impl=%impl% src\rho-structure\export.c"

set "test_array=test\structure\array.c"
set "test_map=test\structure\map.c"

%compiler% --std=c99 %impl% %test_array% -o bin\structure_array.exe
%compiler% --std=c99 %impl% %test_map%   -o bin\structure_map.exe
