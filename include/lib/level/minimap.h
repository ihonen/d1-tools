#pragma once

#include <stdint.h>

// -----------------------------------------------------------------------------

#include "lib/image/fwd.h"
#include "lib/level/fwd.h"

// -----------------------------------------------------------------------------

D1Minimap* D1Minimap_newFromBgndSector(
    const uint8_t* sectorDataBegin,
    uint32_t sectorDataSize
);

void D1Minimap_free(
    D1Minimap* minimap
);

const Bgr888* D1Minimap_pixels(
    const D1Minimap* minimap
);

uint16_t D1Minimap_width(
    const D1Minimap* minimap
);

uint16_t D1Minimap_height(
    const D1Minimap* minimap
);
