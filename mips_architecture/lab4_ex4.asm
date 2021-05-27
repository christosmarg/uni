.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10
.eqv SYS_PRINT_CHAR     11

.data
        msg:    .asciiz "Number: "
        errstr: .asciiz "Give a positive number.\n"

.text
.globl main

main:
        li      $v0, SYS_PRINT_STRING
        la      $a0, msg
        syscall
        
        li      $v0, SYS_READ_WORD
        syscall
        move    $t0, $v0
        
        # exit if t0 <= 0
        beq     $t0, $zero, err
        slt     $t1, $t0, $zero
        bne     $t1, $zero, err
        
        # init loop counter
        li      $t2, 0
        
loop:
        beq     $t2, $t0, exit
        addi    $t2, $t2, 1
        
        li      $v0, SYS_PRINT_CHAR
        li      $a0, '*'
        syscall
        
        j       loop
        
        li      $v0, SYS_PRINT_CHAR
        li      $a0, 0xa
        syscall
        
err:
        li      $v0, SYS_PRINT_STRING
        la      $a0, errstr
        syscall

exit:
        li      $v0, SYS_EXIT
        syscall
