.section .text.boot
.global _start

.extern kernel_main

_start:
    bl kernel_main

1:
    wfe
    b 1b