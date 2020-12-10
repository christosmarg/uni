.eqv SYS_PRINT_STRING   4
.eqv SYS_READ_STRING    8
.eqv SYS_EXIT           10
.eqv SYS_PRINT_CHAR     11

.data
        str:    .space 17 # + 2 bytes to include '\n' and '\0'
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
        beqz    $a0, strrev
        addi    $t0, $t0, 1
        addi    $t1, $t1, 1
        j       strlen
        
        # subtract 2 so that we skip '\n' and '\0' and get to the
        # last character in the string
        addi    $t1, $t1, -2

strrev:
        # if $t0 is 0 is means we reached str[0]
        beqz    $t0, exit
        # in the first loop, $t1 is at the last actual character,
        # so we'll go backwards to get to the beginning
        lb      $a0, 0($t1)
        li      $v0, SYS_PRINT_CHAR
        syscall
        addi    $t0, $t0, -1
        addi    $t1, $t1, -1
        j       strrev
                
exit:                           
        li      $v0, SYS_EXIT
        syscall
