@ECHO OFF

set /p "program=Program name: "

:: Cd to program directory
cd %program%

:: Create (if missing) obj and exec directories
if not exist obj md obj
if not exist exec md exec

:: Cd to source code directory
cd src

:: Compile and move object files to the right directory
gcc -c main.c %program%-libs.c
move main.o ../obj && move %program%-libs.o ../obj
cd ../obj

:: Link and move executable to the right directory
gcc main.o %program%-libs.o -lm
move a.out ../exec
cd ../exec

:: Execute program
a.exe