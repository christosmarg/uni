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
        str1: .asciiz "Hello\n"
        str2: .asciiz "TEI\n"
        name: .space 64
        
.text
.globl _main

_main:
        # 1. print a character
        li      $v0, SYS_PRINT_CHAR
        li      $a0, 'C'
        syscall
        
        endl()
        
        # 2. print characters 'a' and 'd'
        li      $a0, 'a'
        syscall
        li      $a0, 'd'
        syscall
        
        endl()
        
        # 3. print 'Hello'
        li      $v0, SYS_PRINT_STRING
        la      $a0, str1
        syscall
        
        # 4. print 'Hello' and 'TEI'
        la      $a0, str1
        syscall
        la      $a0, str2
        syscall
        
        # 5. print 5
        li      $v0, SYS_PRINT_WORD
        li      $a0, 5
        syscall
        
        endl()
        
        # 6. read a word and print it
        li      $v0, SYS_READ_WORD
        syscall
        move    $t0, $v0
        li      $v0, SYS_PRINT_WORD
        la      $a0, 0($t0)
        syscall
        
        endl()
        
        # 7. read name, store in mem and print it
        li      $v0, SYS_READ_STRING
        la      $a0, name
        li      $a1, 64
        syscall
        li      $v0, SYS_PRINT_STRING
        syscall
        
        li      $v0, SYS_EXIT
        syscall
