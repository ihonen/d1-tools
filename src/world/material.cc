#include "world/material.hh"

// -----------------------------------------------------------------------------

Material::Material(
    const std::vector<Coord2d>& area,
    uint8_t unknownByte00
)
    : m_area(area)
    , m_unknownByte00(unknownByte00)
{
}

const std::vector<Coord2d>& Material::area() const
{
    return m_area;
}

uint8_t Material::unknownByte00() const
{
    return m_unknownByte00;
}
