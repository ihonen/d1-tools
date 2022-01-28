#pragma once

#include "world/coord.hh"
#include "world/worlditem.hh"

#include <cstdint>
#include <vector>

// -----------------------------------------------------------------------------

class Material
    : public WorldItem
{
public:

    enum class Type : uint8_t
    {
        Wood,
        Grass,
        Water,
        Brush,
        Light
    };

    Material(
        const std::vector<Coord2d>& area,
        uint8_t unknownByte00
    );

    const std::vector<Coord2d>& area() const;

    uint8_t unknownByte00() const;

private:

    std::vector<Coord2d> m_area;

    uint8_t m_unknownByte00;
};
