@echo off
cd /d %~dp0

set filename=program
call :compile %1
.\%filename%
del %filename%.exe

exit /b 0

:compile
echo Compiling...
gcc -o %filename% %1
echo Compile finished.
exit /b