@echo off
gcc -o mhs src\*.c -lws2_32 -lpthread -s -w
IF ERRORLEVEL 1 pause