#pragma once

#include <cstdint>

// -----------------------------------------------------------------------------

#pragma pack(push, 1)
struct Coord2d
{
    uint16_t x;
    uint16_t y;
};

struct Coord3d
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t zLayer;
};
#pragma pack(pop)

static_assert(sizeof(Coord2d) == 4);
