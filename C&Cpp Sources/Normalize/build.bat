@echo off
gcc -o normalize.exe *.c -s -w
IF ERRORLEVEL 1 pause