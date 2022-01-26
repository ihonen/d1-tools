#include "level/door.hh"

// -----------------------------------------------------------------------------

Door::Door(
    const std::vector<Coord>& outlineCoords,
    const Coord& frontCoord,
    const Coord& onCoord,
    const Coord& inCoord
)
    : m_outlineCoords(outlineCoords)
    , m_frontCoord(frontCoord)
    , m_onCoord(onCoord)
    , m_inCoord(inCoord)
{
}

const std::vector<Coord>& Door::outlineCoords() const
{
    return m_outlineCoords;
}

const Coord& Door::frontCoord() const
{
    return m_frontCoord;
}

const Coord& Door::onCoord() const
{
    return m_onCoord;
}

const Coord& Door::inCoord() const
{
    return m_inCoord;
}
