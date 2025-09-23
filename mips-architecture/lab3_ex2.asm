.eqv SYS_PRINT_WORD     1
.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_READ_STRING    8
.eqv SYS_EXIT           10
.eqv SYS_PRINT_CHAR     11
.eqv SYS_READ_CHAR      12

.macro endl()
        li      $v0, SYS_PRINT_CHAR
        li      $a0, 0xa
        syscall
.end_macro

.data
        str: .asciiz "hello\n"
       	name: .space 64
        x: .word 0
        a: .word 20
        b: .word 30
        c: .word 15

.text
.globl main

main:   
        # 1. print 1st and 2nd character in string
        li      $v0, SYS_PRINT_CHAR
        lb      $a0, str
        syscall
        lb      $a0, str + 1
        syscall
        
        endl()
        
        # 2. read x and print str[x]
        li      $v0, SYS_READ_WORD
        syscall
        lb      $a0, str($v0)
        li      $v0, SYS_PRINT_CHAR
        syscall
        
        endl()
        
        # 3. read a string and print its 2nd char
        li      $v0, SYS_READ_STRING
        la      $a0, name
        la      $a1, 64
        syscall
        lb      $a0, name + 1
        li      $v0, SYS_PRINT_CHAR
        syscall
        
        endl()
        
        # 4. int x, a = 20, b = 30, c = 15;
        #    x = (a + b) - (c + 10);
        lw      $t0, x
        lw      $t1, a
        lw      $t2, b
        lw      $t3, c
        add     $t4, $t1, $t2
        addi    $t5, $t3, 10
        sub     $t0, $t4, $t5
        
        li      $v0, SYS_PRINT_WORD
        la      $a0, 0($t0)
        syscall
        
        endl()
        
        li      $v0, SYS_EXIT
        syscall
