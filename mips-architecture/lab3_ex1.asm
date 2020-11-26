.data
        str1: .asciiz "Hello\n"
        str2: .asciiz "TEI\n"
        name: .space 64
        
.text
.globl main

main:
        # 1. print a character
        li      $v0, 11
        la      $a0, 'C'
        syscall
        
        # 2. print characters 'a' and 'd'
        li      $a0, 'a'
        syscall
        li      $a0, 'd'
        syscall
        
        # 3. print 'Hello'
        li      $v0, 4
        la      $a0, str1
        syscall
        
        # 4. print 'Hello' and 'TEI'
        la      $a0, str1
        syscall
        la      $a0, str2
        syscall
        
        # 5. print 5
        li      $v0, 1
        li      $a0, 5
        syscall
        
        # 6. read a word and print it
        li      $v0, 5
        syscall
        move    $t0, $v0
        li      $v0, 1
        la      $a0, 0($t0)
        syscall
        
        # 7. read name, store in mem and print it
        li      $v0, 8
        la      $a0, name
        li      $a1, 64
        syscall
        li      $v0, 4
        syscall
        
        li      $v0, 10
        syscall
