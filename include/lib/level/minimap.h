#pragma once

#include <stdint.h>

// -----------------------------------------------------------------------------

#include "lib/image/fwd.h"
#include "lib/level/fwd.h"

// -----------------------------------------------------------------------------

D1Minimap* D1Minimap_new(
    uint16_t width,
    uint16_t height,
    const Bgr888* pixels
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
