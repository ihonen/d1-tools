#pragma once

#include <stdint.h>

// ---------------------------------------------------------------------------

typedef struct D1Minimap D1Minimap;

// ---------------------------------------------------------------------------

D1Minimap* d1_parseDvdBgndSectorData(
    const uint8_t* firstByteOfData,
    uint32_t dataSize
);
