#include "../include/kernel.hpp"

namespace AthKernel
{

void Initialize()
{
    // Kernel starts here.

    while (true)
    {
        asm volatile("wfe");
    }
}

}