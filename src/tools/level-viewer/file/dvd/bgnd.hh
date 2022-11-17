#pragma once

#include <cstdint>

// ---------------------------------------------------------------------------

class Minimap;

// ---------------------------------------------------------------------------

std::shared_ptr<Minimap> parseBgndSector(
    const uint8_t* firstByteOfData,
    uint32_t dataSize
);
