#pragma once

#include <stdint.h>

namespace Mailbox
{
    constexpr uint32_t ChannelProperty = 8;

    bool Call(uint8_t channel);
}