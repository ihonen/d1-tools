#include "level/door.hh"

// -----------------------------------------------------------------------------

Door::Door(
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
)
    : m_parent(nullptr)
    , m_outlineCoords(outlineCoords)
    , m_entryCoords(entryCoords)
    , m_type(type)
    , m_locked(locked)
    , m_unknownByte01(unknownByte01)
    , m_lockPickable(lockPickable)
    , m_unknownByte04(unknownByte04)
    , m_unknownByte05(unknownByte05)
    , m_unknownByte06(unknownByte06)
    , m_unknownByte07(unknownByte07)
    , m_unknownByte08(unknownByte08)
    , m_unknownByte09(unknownByte09)
{
}

void Door::setParent(const Building* parent)
{
    m_parent = parent;
}

const Building* Door::parent() const
{
    return m_parent;
}

const std::vector<Coord2d>& Door::outlineCoords() const
{
    return m_outlineCoords;
}

const std::vector<Coord3d>& Door::entryCoords() const
{
    return m_entryCoords;
}

uint8_t Door::type() const
{
    return m_type;
}

uint8_t Door::locked() const
{
    return m_locked;
}

uint8_t Door::unknownByte01() const
{
    return m_unknownByte01;
}

uint8_t Door::lockPickable() const
{
    return m_lockPickable;
}

uint8_t Door::unknownByte04() const
{
    return m_unknownByte04;
}

uint8_t Door::unknownByte05() const
{
    return m_unknownByte05;
}

uint8_t Door::unknownByte06() const
{
    return m_unknownByte06;
}

uint8_t Door::unknownByte07() const
{
    return m_unknownByte07;
}

uint8_t Door::unknownByte08() const
{
    return m_unknownByte08;
}

uint8_t Door::unknownByte09() const
{
    return m_unknownByte09;
}
