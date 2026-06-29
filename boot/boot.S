.section .text
.global _start

.extern kernel_main

_start:

    // Call the C++ kernel
    bl kernel_main

1:
    wfe
    b 1b