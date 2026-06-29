#pragma once

#include <stdint.h>

namespace Framebuffer
{

struct Info
{
    uint32_t* Address;

    uint32_t Width;
    uint32_t Height;

    uint32_t Pitch;
};

bool Initialize();

Info& Get();

void PutPixel(
    uint32_t x,
    uint32_t y,
    uint32_t color
);

}