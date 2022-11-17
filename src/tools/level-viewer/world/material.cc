#include "world/material.hh"

// -----------------------------------------------------------------------------

MaterialZone::MaterialZone(
    Type type,
    unsigned sectionNumber,
    const std::vector<Coord2d>& outlineCoords,
    uint16_t unknownWord00,
    std::optional<uint8_t> unknownByte00,
    std::optional<uint8_t> unknownByte01,
    std::optional<uint8_t> unknownByte02,
    std::optional<uint8_t> unknownByte03,
    std::optional<uint8_t> unknownByte04,
    std::optional<uint8_t> unknownByte05,
    std::optional<uint8_t> unknownByte06,
    std::optional<uint32_t> unknownDword00
)
    : m_type(type)
    , m_outlineCoords(outlineCoords)
    , m_sectionNumber(sectionNumber)
    , m_unknownWord00(unknownWord00)
    , m_unknownByte00(unknownByte00)
    , m_unknownByte01(unknownByte01)
    , m_unknownByte02(unknownByte02)
    , m_unknownByte03(unknownByte03)
    , m_unknownByte04(unknownByte04)
    , m_unknownByte05(unknownByte05)
    , m_unknownByte06(unknownByte06)
    , m_unknownDword00(unknownDword00)
{
}

MaterialZone::Type MaterialZone::type() const
{
    return m_type;
}

std::string MaterialZone::typeToString() const
{
    switch (m_type)
    {
    case Type::Unknown: return "Unknown";
    case Type::Wood:    return "Wood";
    case Type::Grass:   return "Grass";
    case Type::Water:   return "Water";
    case Type::Brush:   return "Brush";
    case Type::Light:   return "Light";
    }

    return "<UNKNOWN>";
}

const std::vector<Coord2d>& MaterialZone::outlineCoords() const
{
    return m_outlineCoords;
}

unsigned MaterialZone::sectionNumber() const
{
    return m_sectionNumber;
}

uint16_t MaterialZone::unknownWord00() const
{
    return m_unknownWord00;
}

std::optional<uint8_t> MaterialZone::unknownByte00() const
{
    return m_unknownByte00;
}

std::optional<uint8_t> MaterialZone::unknownByte01() const
{
    return m_unknownByte01;
}

std::optional<uint8_t> MaterialZone::unknownByte02() const
{
    return m_unknownByte02;
}

std::optional<uint8_t> MaterialZone::unknownByte03() const
{
    return m_unknownByte03;
}

std::optional<uint8_t> MaterialZone::unknownByte04() const
{
    return m_unknownByte04;
}

std::optional<uint8_t> MaterialZone::unknownByte05() const
{
    return m_unknownByte05;
}

std::optional<uint8_t> MaterialZone::unknownByte06() const
{
    return m_unknownByte06;
}

std::optional<uint32_t> MaterialZone::unknownDword00() const
{
    return m_unknownDword00;
}
