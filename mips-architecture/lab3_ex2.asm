.data
        str1: .ascii "hello"
        str2: .space 64
        x: .word 0
        a: .word 20
        b: .word 30
        c: .word 15

.text
.globl main

main:
        # 1. print 1st and 2nd character in string
        li      $v0, 11
        lb      $a0, str1
        syscall
        lb      $a0, str1 + 1
        syscall
        
        # 2. read x and print str[x]
        li      $v0, 5
        syscall
        lb      $a0, str1 + 0($v0)
        li      $v0, 11
        syscall
        
        # 3. read a string and print its 2nd char
        li      $v0, 8
        la      $a0, str2
        la      $a1, 64
        syscall
        lb      $a0, str2 + 1
        li      $v0, 11
        syscall
        
        # 4. int x, a = 20, b = 30, c = 15;
        #    x = (a + b) - (c + 10);
        lw      $t0, x
        lw      $t1, a
        lw      $t2, b
        lw      $t3, c
        add     $t4, $t1, $t2
        addi    $t5, $t3, 10
        sub     $t0, $t4, $t5
        
        li      $v0, 1
        la      $a0, 0($t0)
        syscall  
        
        li $v0, 10
        syscall
