#pragma once

#include "world/building.hh"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------

std::pair<std::vector<std::shared_ptr<Building>>, std::vector<std::shared_ptr<Door>>>
parseBuilSector(
    const std::string levelName,
    const uint8_t* firstByteOfData,
    uint32_t dataSize
);
