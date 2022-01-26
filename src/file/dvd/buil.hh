#pragma once

#include "level/building.hh"

#include <cstdint>
#include <memory>
#include <vector>

// ---------------------------------------------------------------------------

std::vector<std::shared_ptr<Building>> parseBuilSector(
    const uint8_t* firstByteOfData,
    uint32_t dataSize
);
