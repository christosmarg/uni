#!/bin/bash

# Cd to program directory
cd $1

# Create (if missing) obj and include directories
mkdir -p obj exec

# Cd to source code directory
cd src

# Compile and move new files to the right directory
gcc -c main.c $1-libs.c && mv main.o $1-libs.o ../obj && cd ../obj;
gcc main.o $1-libs.o -lm && mv a.out ../exec && cd ../exec;

# Execute program
./a.out