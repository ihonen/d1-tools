#pragma once

#include <stdint.h>

// ---------------------------------------------------------------------------

typedef struct D1Minimap D1Minimap;

// ---------------------------------------------------------------------------

D1Minimap* d1_parseBgndSectorData(
    const uint8_t* first_byte
);
