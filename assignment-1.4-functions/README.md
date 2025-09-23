# Compilation, Linking & Execution steps

* ```program``` = program's name
* ```..../``` = full path
* ```$``` = terminal command

## Linux

### Method 1

1. Open a terminal emulator, or the integrated terminal of your editor.
2. Move to the ```src``` directory of the program: ```$ cd ..../assignment-1.4-functions/program/src```
3. Compile ```main.c``` and ```program-libs.c```: ```$ gcc -c main.c program-libs.c && mv main.o program-libs.o ../obj && cd ../obj```
4. Link ```main.o``` and ```program-libs.o```: ```$ gcc main.o program-libs.o -lm && mv a.out ../exec && cd ../exec```
5. Execute program: ```$ ./a.out```

### Method 2

1. Open a terminal emulator, or the integrated terminal of your editor.
2. Move to the ```programs``` directory: ```$ cd …./assignment-1.4-functions```
3. _In case step 4 fails, do this first_: ```$ chmod +x autocompile.sh```
4. Run the ```autocompile.sh``` script: ```$ ./autocompile.sh program```

## Windows

__Requirements:__ MinGW gcc compiler

### Method 1

1. Open Command Prompt, or the integrated terminal of your editor.
2. Move to the ```src``` directory of the program: ```$ cd ..../assignment-1.4-functions/program/src```
3. Compile ```main.c``` and ```program-libs.c```: ```$ gcc -c main.c program-libs.c && mv main.o program-libs.o ../obj && cd ../obj```
4. Link ```main.o``` and ```program-libs.o```: ```$ gcc main.o program-libs.o -lm && mv a.out ../exec && cd ../exec```
5. Execute program: ```$ ./a.exe```

### Method 2

1. Open Command Prompt, or the integrated terminal of your editor.
2. Move to the ```programs``` directory: ```cd ..../assignment-1.4-functions```
3. Run the ```autocompile.bat``` script: ```autocompile```
4. Enter the name of the program __exactly__ as it's written in the folder when the script prints ```"Program name: "```



In case you want to compile and run ```hanoi-tower```, just do: ```$ gcc -c hanoi-tower.c && gcc hanoi-tower.o && ./a.out```