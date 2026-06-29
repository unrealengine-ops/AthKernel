// drivers/uart.cpp
// PL011 UART Driver for Raspberry Pi 5 (BCM2712)
// Copyright (c) 2026 Atharv Srivastav

// For a 64-bit architecture, we use unsigned long for 64-bit memory addresses
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

#define PERIPHERAL_BASE 0x107D000000ULL
#define UART0_BASE      (PERIPHERAL_BASE + 0x30000)

// Define the PL011 UART Register offsets
#define UART0_DR        ((volatile uint32_t*)(UART0_BASE + 0x00))
#define UART0_FR        ((volatile uint32_t*)(UART0_BASE + 0x18))
#define UART0_IBRD      ((volatile uint32_t*)(UART0_BASE + 0x24))
#define UART0_FBRD      ((volatile uint32_t*)(UART0_BASE + 0x28))
#define UART0_LCRH      ((volatile uint32_t*)(UART0_BASE + 0x2C))
#define UART0_CR        ((volatile uint32_t*)(UART0_BASE + 0x30))

extern "C" void uart_init() {
    // Disable UART0 while we configure it
    *UART0_CR = 0;

    // Set baud rate parameters for the Pi 5's default UART clock frequencies
    // For a standard 115200 baud rate:
    *UART0_IBRD = 26;
    *UART0_FBRD = 3;

    // Line Control: 8-bit word length, enable FIFO buffers
    *UART0_LCRH = (1 << 4) | (1 << 5) | (1 << 6);

    // Re-enable UART: Enable TX (Transmit), RX (Receive), and the UART itself
    *UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

extern "C" void uart_putc(char c) {
    // Wait until the Transmit FIFO is not full (Bit 5 in Flag Register is TXFF)
    while (*UART0_FR & (1 << 5)) {
        asm volatile("nop");
    }
    // Write character to Data Register
    *UART0_DR = c;
}

extern "C" void uart_puts(const char* str) {
    while (*str) {
        // If we hit a newline, handle carriage return for the terminal interface
        if (*str == '\n') {
            uart_putc('\r');
        }
        uart_putc(*str++);
    }
}