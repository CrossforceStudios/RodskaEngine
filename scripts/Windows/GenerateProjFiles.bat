@echo OFF
PUSHD ..\..\
call vendor\bin\premake5\premake5.exe vs2019
POPD
PAUSE

