@echo off
setlocal

echo [1/2] Compilando programa...
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src\main.c src\grafo.c -Iinclude -o programa.exe
if errorlevel 1 goto :erro

echo [2/2] Compilando testes...
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 tests\test_grafo.c src\grafo.c -Iinclude -o testes.exe
if errorlevel 1 goto :erro

echo.
echo Compilacao concluida.
echo Execute testes.exe para rodar os testes.
echo Execute programa.exe para rodar a demonstracao.
goto :fim

:erro
echo.
echo ERRO: confira se o GCC esta instalado e disponivel no PATH.
exit /b 1

:fim
endlocal
