.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10
.eqv SYS_PRINT_CHAR     11

.macro input(%msg)
        li      $v0, SYS_PRINT_STRING
        la      $a0, %msg
        syscall
        
        li      $v0, SYS_READ_WORD
        syscall
.end_macro

.macro ispositive(%val)
        # exit if t0 or $t1 <= 0
        beq     %val, $zero, err
        slt     $t2, %val, $zero
        bne     $t2, $zero, err
.end_macro

.data
        msg1:   .asciiz "Lines: "
        msg2:   .asciiz "Chars: "
        errstr: .asciiz "Give positive numbers only.\n"

.text
.globl main

main:
        input(msg1)
        move    $t0, $v0
        
        input(msg2)
        move    $t1, $v0
        
        ispositive($t0)
        ispositive($t1)
        
        # init outer loop counter
        li      $t3, 0
        
outloop:
        # exit if t3 == x
        beq     $t3, $t0, exit
        addi    $t3, $t3, 1

        # init inner loop counter
        li      $t4, 0

        # print newline
        li      $v0, SYS_PRINT_CHAR
        li      $a0, 0xa
        syscall
        j       inloop
        
        j       outloop 
        
inloop:
        # break inner loop if t4 == y
        beq     $t4, $t1, outloop
        addi    $t4, $t4, 1
        
        li      $v0, SYS_PRINT_CHAR
        li      $a0, '*'
        syscall
        
        j       inloop

err:
        li      $v0, SYS_PRINT_STRING
        la      $a0, errstr
        syscall

exit:
        li      $v0, SYS_EXIT
        syscall
