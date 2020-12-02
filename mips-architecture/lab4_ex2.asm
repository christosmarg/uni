.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10

.data
        posstr:    .asciiz "Positive\n"
        nonposstr: .asciiz "Non Positive\n"

.text
.globl main

main:
        li      $v0, SYS_READ_WORD
        syscall
        
        # t0 = 1 if v0 == 0
        slt     $t0, $v0, $zero
        beq     $t0, $zero, pos
        
        li      $v0, SYS_PRINT_STRING
        la      $a0, nonposstr
        syscall
         
        j       exit
        
pos:
        li      $v0, SYS_PRINT_STRING
        la      $a0, posstr
        syscall
        
        j exit
        
exit:
        li      $v0, SYS_EXIT
        syscall
