#pragma once

#include "world/coord.hh"
#include "world/worlditem.hh"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

// -----------------------------------------------------------------------------

class MaterialZone
    : public WorldItem
{
public:

    enum class Type : uint8_t
    {
        Unknown = 0x00,
        Wood    = 0x01,
        Grass   = 0x03,
        Water   = 0x05,
        Brush   = 0x06,
        Light   = 0x08,
    };

    MaterialZone(
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
    );

    Type type() const;

    std::string typeToString() const;

    const std::vector<Coord2d>& outlineCoords() const;

    unsigned sectionNumber() const;

    uint16_t unknownWord00() const;
    std::optional<uint8_t> unknownByte00() const;
    std::optional<uint8_t> unknownByte01() const;
    std::optional<uint8_t> unknownByte02() const;
    std::optional<uint8_t> unknownByte03() const;
    std::optional<uint8_t> unknownByte04() const;
    std::optional<uint8_t> unknownByte05() const;
    std::optional<uint8_t> unknownByte06() const;
    std::optional<uint32_t> unknownDword00() const;

private:

    Type m_type;

    std::vector<Coord2d> m_outlineCoords;

    uint16_t m_unknownWord00;
    std::optional<uint8_t> m_unknownByte00;
    std::optional<uint8_t> m_unknownByte01;
    std::optional<uint8_t> m_unknownByte02;
    std::optional<uint8_t> m_unknownByte03;
    std::optional<uint8_t> m_unknownByte04;
    std::optional<uint8_t> m_unknownByte05;
    std::optional<uint8_t> m_unknownByte06;
    std::optional<uint32_t> m_unknownDword00;

    unsigned m_sectionNumber;
};
