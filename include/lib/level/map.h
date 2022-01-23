#pragma once

#include <stdint.h>

// -----------------------------------------------------------------------------

#include "lib/image/fwd.h"
#include "lib/level/fwd.h"

// -----------------------------------------------------------------------------

D1Map* D1Map_newFromDvmFile(
    const char* path,
    D1Level* parentLevel
);

void D1Map_free(
    D1Map* map
);

D1Level* D1Map_parentLevel(
    const D1Map* map
);

const Bgr888* D1Map_pixels(
    const D1Map* map
);

uint16_t D1Map_width(
    const D1Map* map
);

uint16_t D1Map_height(
    const D1Map* map
);

uint32_t D1Map_numPixels(
    const D1Map* map
);
