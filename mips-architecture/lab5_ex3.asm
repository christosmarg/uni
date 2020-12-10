.eqv SYS_EXIT 10

.data
        size:   .byte 10
        arr:    .byte 1, 15, 0, -3, 99, 48, -17, -9, 20, 15

.text
.globl main

main:
        # init loop, sum counters and define iterations
        li      $t0, 0
        li      $t1, 0
        lb      $t2, size

calcsum:
        beq     $t0, $t2, exit
        lb      $t3, arr($t0)
        add     $t1, $t1, $t3
        addi    $t0, $t0, 1
        j       calcsum

exit:
        li      $v0, SYS_EXIT
        syscall
