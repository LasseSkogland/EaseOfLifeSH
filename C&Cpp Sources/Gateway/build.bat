@echo off
gcc server.c -o bin\server -s -w -O3 -lws2_32 -lpthread
IF ERRORLEVEL 1 goto error
gcc client.c -o bin\client -s -w -O3 -lws2_32
IF ERRORLEVEL 1 goto error
goto exit
:error
pause
:exit