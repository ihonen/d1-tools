#pragma once

#include "world/material.hh"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------

std::vector< std::shared_ptr<Material>> parseMatSector(
    const std::string levelName,
    const uint8_t* firstByteOfData,
    uint32_t dataSize
);
