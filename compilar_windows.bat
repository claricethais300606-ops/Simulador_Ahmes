@echo off
if not exist build mkdir build
gcc -std=c11 -Wall -Wextra -pedantic -Isrc/nucleo -Isrc/interface src\main.c src\nucleo\*.c src\interface\*.c tests\*.c -o build\ahmes.exe
if errorlevel 1 exit /b 1
echo Compilado: build\ahmes.exe
