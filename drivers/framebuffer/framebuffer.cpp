#include "framebuffer.hpp"

namespace
{

Framebuffer::Info gFramebuffer =
{
    nullptr,
    0,
    0,
    0
};

}

namespace Framebuffer
{

bool Initialize()
{
    // mailbox initialization comes next
return false;
    
}

Info& Get()
{
    return gFramebuffer;
}

void PutPixel(
    uint32_t x,
    uint32_t y,
    uint32_t color
)
{
    if (!gFramebuffer.Address)
        return;

    gFramebuffer.Address[
        y * (gFramebuffer.Pitch / 4) + x
    ] = color;
}
 
}