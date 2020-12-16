@echo off
cd /d %~dp0

set filename=program
call :compile %1
a.exe
del a.exe

exit /b 0

:compile
echo Compiling...
gcc %1
echo Compile finished.
exit /b