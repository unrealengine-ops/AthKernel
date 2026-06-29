#include "cpu.hpp"

namespace CPU
{

void Halt()
{
    while (true)
    {
        asm volatile("wfe");
    }
}

void Wait()
{
    asm volatile("wfe");
}

void EnableInterrupts()
{
    asm volatile("msr daifclr, #2");
}

void DisableInterrupts()
{
    asm volatile("msr daifset, #2");
}

}