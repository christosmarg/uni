.eqv SYS_EXIT 10

.data
        val:    .word 0xabcd
        # 'val' is 2 bytes
        first:  .space 2
        second: .space 2
        third:  .space 2
        fourth: .space 2

.text
.globl main

main:
        # init loop counter
        li      $t0, 0
        # 4 iterations because we'll store 'val' 4 times
        li      $t1, 4
        # this is our offset, we'll increment it by 2
        # in each iteration so that we store 0xabcd in
        # the appropriate label
        li      $t2, 0
        lh      $t3, val
        
loop:
        beq     $t0, $t1, exit
        # store it as half word so that it and doesn't
        # there aren't any zeros between that and the next 'val'
        sh      $t3, first($t2)
        addi    $t0, $t0, 1
        addi    $t2, $t2, 2
        j       loop

exit:
        li      $v0, SYS_EXIT
        syscall
