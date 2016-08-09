@echo off
del test.exe libeasy.dll>NUL 2>&1
gcc src\*.c -o libeasy.dll -shared -lws2_32 -s -Werror
IF ERRORLEVEL 1 goto DLL
gcc test.c -o test.exe libeasy.dll -Isrc\ -s
IF ERRORLEVEL 1 goto EXE
goto exit
:DLL
echo Error with DLL
pause
goto exit
:EXE
echo Error with EXE
pause
goto exit
:exit