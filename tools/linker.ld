ENTRY(_start)

SECTIONS
{
    /* The Raspberry Pi 5 firmware loads our kernel at this exact memory address */
    . = 0x80000; 

    .text : {
        KEEP(*(.text.boot))
        *(.text .text.* .gnu.linkonce.t.*)
    }

    .rodata : {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    }

    .data : {
        *(.data .data.* .gnu.linkonce.d.*)
    }

    .bss : {
        sbss = .;
        *(.bss .bss.*)
        *(COMMON)
        ebss = .;
    }

    /DISCARD/ : { *(.comment) *(.gnu.attributes) *(.eh_frame) }
}