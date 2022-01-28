#pragma once

#include "world/coord.hh"

#include <cstdint>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------

std::vector<std::vector<Coord2d>> parseMatSector(
    const std::string levelName,
    const uint8_t* firstByteOfData,
    uint32_t dataSize
);
