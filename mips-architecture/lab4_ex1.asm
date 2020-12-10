.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_WORD      5
.eqv SYS_EXIT           10

.data
        zstr:  .asciiz "Zero\n"
        nzstr: .asciiz "Non Zero\n"
        
.text
.globl main

main:	
        li      $v0, SYS_READ_WORD
        syscall
        
        bne     $v0, $zero, nonzero
        li      $v0, SYS_PRINT_STRING
        la      $a0, zstr
        syscall
        
        j       exit
        
nonzero:
        li      $v0, SYS_PRINT_STRING
        la      $a0, nzstr
        syscall
        
exit:   
        li      $v0, SYS_EXIT
        syscall