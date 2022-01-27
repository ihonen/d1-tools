#pragma once

#include "level/coord.hh"
#include "level/worlditem.hh"

#include <memory>
#include <string>
#include <vector>

// -----------------------------------------------------------------------------

class Building;

// -----------------------------------------------------------------------------

class Door
    : public WorldItem
{
public:

    enum class Type : uint8_t
    {
        Invisible = 0x00,
        Normal    = 0x01,
        Trapdoor  = 0x02,
        Special   = 0x03
    };

    Door(
        const std::vector<Coord2d>& outlineCoords,
        const std::vector<Coord3d>& entryCoords,
        Type type,
        uint8_t unknownByte01,
        uint8_t locked,
        uint8_t lockPickable,
        uint8_t unknownByte04,
        uint8_t unknownByte05,
        uint8_t unknownByte06,
        uint8_t unknownByte07,
        uint8_t unknownByte08,
        uint8_t unknownByte09,
        uint16_t unknownWord00,
        uint8_t unknownByte10,
        uint8_t unknownByte11
    );

    const std::vector<Coord2d>& outlineCoords() const;
    const std::vector<Coord3d>& entryCoords() const;

    void setParent(const Building* parent);
    const Building* parent() const;

    Type type() const;
    std::string typeToString() const;
    uint8_t unknownByte01() const;
    uint8_t locked() const;
    uint8_t lockPickable() const;
    uint8_t unknownByte04() const;
    uint8_t unknownByte05() const;
    uint8_t unknownByte06() const;
    uint8_t unknownByte07() const;
    uint8_t unknownByte08() const;
    uint8_t unknownByte09() const;
    uint16_t unknownWord00() const;
    uint8_t unknownByte10() const;
    uint8_t unknownByte11() const;

private:

    const Building* m_parent;

    std::vector<Coord2d> m_outlineCoords;
    std::vector<Coord3d> m_entryCoords;

    Type m_type;
    uint8_t m_unknownByte01;
    uint8_t m_locked;
    uint8_t m_lockPickable;
    uint8_t m_unknownByte04;
    uint8_t m_unknownByte05;
    uint8_t m_unknownByte06;
    uint8_t m_unknownByte07;
    uint8_t m_unknownByte08;
    uint8_t m_unknownByte09;
    uint16_t m_unknownWord00;
    uint8_t m_unknownByte10;
    uint8_t m_unknownByte11;
};
