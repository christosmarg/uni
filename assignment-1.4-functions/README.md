# Compilation, Linking & Execution steps

* ```program_name``` = program's name
* ```full_path/``` = full path
* ```$``` = terminal command (__don't__ copy it)

## Linux

### Method 1

1. Open a terminal emulator, or the integrated terminal of your editor.
2. Move to the ```src``` directory of the program: ```$ cd full_path/assignment-1.4-functions/program_name/src```
3. Compile ```main.c``` and ```program_name-libs.c```: ```$ gcc -c main.c program_name-libs.c && mv main.o program_name-libs.o ../obj && cd ../obj```
4. Link ```main.o``` and ```program_name-libs.o```: ```$ gcc main.o program_name-libs.o -lm && mv a.out ../exec && cd ../exec```
5. Execute program: ```$ ./a.out```

### Method 2

1. Open a terminal emulator, or the integrated terminal of your editor.
2. Move to the assignment's directory: ```$ cd full_path/assignment-1.4-functions```
3. _In case step 4 fails, do this first_: ```$ chmod +x autocompile.sh```
4. Run the ```autocompile.sh``` script: ```$ ./autocompile.sh program_name```

## Windows

__Requirements:__ MinGW gcc compiler

### Method 1

1. Open Command Prompt, or the integrated terminal of your editor.
2. Move to the ```src``` directory of the program: ```$ cd full_path/assignment-1.4-functions/program_name/src```
3. Compile ```main.c``` and ```program_name-libs.c```: ```$ gcc -c main.c program_name-libs.c && mv main.o program_name-libs.o ../obj && cd ../obj```
4. Link ```main.o``` and ```program_name-libs.o```: ```$ gcc main.o program_name-libs.o -lm && mv a.out ../exec && cd ../exec```
5. Execute program: ```$ a.exe```

### Method 2

1. Open Command Prompt, or the integrated terminal of your editor.
2. Move to the assignment's directory: ```$ cd full_path/assignment-1.4-functions```
3. Run the ```autocompile.bat``` script: ```$ autocompile```
4. Enter the name of the program_name __exactly__ as it's written in the folder when the script prints ```"Program name: "```



In case you want to compile and run ```hanoi-tower```, just do: ```$ gcc -c hanoi-tower.c && gcc hanoi-tower.o && ./a.out```