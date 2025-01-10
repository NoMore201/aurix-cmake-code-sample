#pragma once

#include "types.hpp"

#include <ranges>

namespace Hal::Gpio
{

enum class Function : u8
{
    Input,
    Output
};

enum Speed : u8
{
    cmosAutomotiveSpeed1 = 0,
    cmosAutomotiveSpeed2 = 1,
    cmosAutomotiveSpeed3 = 2,
    cmosAutomotiveSpeed4 = 3,
    ttlSpeed1            = 8,
    ttlSpeed2            = 9,
    ttlSpeed3            = 10,
    ttlSpeed4            = 11,
    ttl3v3Speed1         = 12,
    ttl3v3Speed2         = 13,
    ttl3v3Speed3         = 14,
    ttl3v3Speed4         = 15
};

enum Mode : u8
{
    inputNoPullDevice      = 0,
    inputPullDown          = 8U,
    inputPullUp            = 0x10U,
    outputPushPullGeneral  = 0x80U,
    outputPushPullAlt1     = 0x88U,
    outputPushPullAlt2     = 0x90U,
    outputPushPullAlt3     = 0x98U,
    outputPushPullAlt4     = 0xA0U,
    outputPushPullAlt5     = 0xA8U,
    outputPushPullAlt6     = 0xB0U,
    outputPushPullAlt7     = 0xB8U,
    outputOpenDrainGeneral = 0xC0U,
    outputOpenDrainAlt1    = 0xC8U,
    outputOpenDrainAlt2    = 0xD0U,
    outputOpenDrainAlt3    = 0xD8U,
    outputOpenDrainAlt4    = 0xE0U,
    outputOpenDrainAlt5    = 0xE8U,
    outputOpenDrainAlt6    = 0xF0U,
    outputOpenDrainAlt7    = 0xF8U
};

struct Pin
{
    u8       port;
    u8       number;
    Function function;
    Speed    speed;
    Mode     mode;
};

void configure(const Pin& pin);

void configure(const std::ranges::range auto& pin_list)
{
    for (auto pin : pin_list)
    {
        configure(pin);
    }
}

} // namespace Hal::Gpio