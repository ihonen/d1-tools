#pragma once

#include <cstdint>

// -----------------------------------------------------------------------------

#pragma pack(push, 1)
struct Coord
{
    uint16_t x;
    uint16_t y;
};
#pragma pack(pop)

static_assert(sizeof(Coord) == 4);
