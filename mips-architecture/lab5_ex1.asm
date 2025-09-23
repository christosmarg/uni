.eqv SYS_PRINT_WORD     1
.eqv SYS_READ_STRING    8
.eqv SYS_EXIT           10

.data
        str:    .space 17 # + 2 bytes to include '\n' and '\0'
        len:    .asciiz "strlen: "
        revstr: .asciiz "reverse: "
        
.text
.globl main

main:
        # read input string
        li      $v0, SYS_READ_STRING
        la      $a0, str
        li      $a1, 17
        syscall
        
        # init strlen counter
        li      $t0, 0
        # load string to $t1 because we want to use $a0
        la      $t1, str
        
strlen:
        lb      $a0, 0($t1)
        beqz    $a0, exit
        addi    $t0, $t0, 1
        addi    $t1, $t1, 1
        j       strlen

exit:
        li      $v0, SYS_PRINT_STRING
        la      $a0, len
        syscall
        
        li      $v0, SYS_PRINT_WORD
        la      $a0, 0($t0)
        syscall
                                
        li      $v0, SYS_EXIT
        syscall
