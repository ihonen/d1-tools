#pragma once

#include "level/coord.hh"

#include <vector>

// -----------------------------------------------------------------------------

class Door
{
public:

    Door(
        const std::vector<Coord>& outlineCoords,
        const Coord& frontCoord,
        const Coord& onCoord,
        const Coord& inCoord
    );

    const std::vector<Coord>& outlineCoords() const;

    const Coord& frontCoord() const;

    const Coord& onCoord() const;

    const Coord& inCoord() const;

private:

    std::vector<Coord> m_outlineCoords;
    Coord m_frontCoord;
    Coord m_onCoord;
    Coord m_inCoord;
};
