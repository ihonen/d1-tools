#pragma once

#include "level/coord.hh"
#include "level/worlditem.hh"

#include <memory>
#include <vector>

// -----------------------------------------------------------------------------

class Building;

// -----------------------------------------------------------------------------

class Door
    : public WorldItem
{
public:

    Door(
        const std::vector<Coord2d>& outlineCoords,
        const std::vector<Coord3d>& entryCoords,
        uint8_t type,
        uint8_t locked,
        uint8_t unknownByte01,
        uint8_t lockPickable,
        uint8_t unknownByte04,
        uint8_t unknownByte05,
        uint8_t unknownByte06,
        uint8_t unknownByte07,
        uint8_t unknownByte08,
        uint8_t unknownByte09
    );

    const std::vector<Coord2d>& outlineCoords() const;
    const std::vector<Coord3d>& entryCoords() const;

    void setParent(const Building* parent);
    const Building* parent() const;

    uint8_t type() const;

    uint8_t locked() const;

    uint8_t unknownByte01() const;
    uint8_t lockPickable() const;
    uint8_t unknownByte04() const;
    uint8_t unknownByte05() const;
    uint8_t unknownByte06() const;
    uint8_t unknownByte07() const;
    uint8_t unknownByte08() const;
    uint8_t unknownByte09() const;

private:

    const Building* m_parent;

    std::vector<Coord2d> m_outlineCoords;
    std::vector<Coord3d> m_entryCoords;

    uint8_t m_type;
    uint8_t m_locked;

    uint8_t m_unknownByte01;
    uint8_t m_lockPickable;
    uint8_t m_unknownByte04;
    uint8_t m_unknownByte05;
    uint8_t m_unknownByte06;
    uint8_t m_unknownByte07;
    uint8_t m_unknownByte08;
    uint8_t m_unknownByte09;

};
