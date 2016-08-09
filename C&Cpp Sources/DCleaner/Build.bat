@echo off
gcc -s -O3 -o dcleaner loggerkey.c -luser32 -lkernel32


IF ERRORLEVEL 1 pause