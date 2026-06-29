#include "mailbox.hpp"

namespace
{
    constexpr uint64_t MMIO_BASE = 0xFE000000;

    volatile uint32_t* const MAILBOX_READ =
        (volatile uint32_t*)(MMIO_BASE + 0xB880);

    volatile uint32_t* const MAILBOX_STATUS =
        (volatile uint32_t*)(MMIO_BASE + 0xB898);

    volatile uint32_t* const MAILBOX_WRITE =
        (volatile uint32_t*)(MMIO_BASE + 0xB8A0);

    constexpr uint32_t MAILBOX_FULL  = 0x80000000;
    constexpr uint32_t MAILBOX_EMPTY = 0x40000000;
}

namespace Mailbox
{

alignas(16)
volatile uint32_t Message[36];

bool Call(uint8_t channel)
{
    uint32_t address =
        ((uint64_t)&Message & ~0xF) | (channel & 0xF);

    while (*MAILBOX_STATUS & MAILBOX_FULL)
    {
    }

    *MAILBOX_WRITE = address;

    while (true)
    {
        while (*MAILBOX_STATUS & MAILBOX_EMPTY)
        {
        }

        uint32_t response = *MAILBOX_READ;

        if (response == address)
        {
            return Message[1] == 0x80000000;
        }
    }
}

}