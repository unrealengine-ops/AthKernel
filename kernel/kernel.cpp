#include "../arch/aarch64/cpu.hpp"
#include "../drivers/framebuffer/framebuffer.hpp"
#include "../include/kernel.hpp"

namespace AthKernel
{

void Initialize()
{
    Framebuffer::Initialize();

    CPU::Halt();
}

}