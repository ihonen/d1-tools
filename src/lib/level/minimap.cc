extern "C" {
#include "lib/common/bzip2.h"
#include "lib/image/pixel.h"
#include "lib/level/level.h"
#include "lib/level/minimap.h"
}

#include "lib/common/log.hh"

#include <vector>

// -----------------------------------------------------------------------------

struct D1Minimap
{
    uint16_t width      = 0;
    uint16_t height     = 0;
    std::vector<Bgr888> pixels;
};

// -----------------------------------------------------------------------------

D1Minimap* D1Minimap_new(
    uint16_t width,
    uint16_t height,
    const Bgr888* pixels
)
{
    auto minimap = new D1Minimap;
    minimap->width = width;
    minimap->height = height;
    minimap->pixels = std::vector<Bgr888>(
        pixels,
        pixels + width * height
    );

    return minimap;
}

void D1Minimap_free(
    D1Minimap* minimap
)
{
    delete minimap;
}

const Bgr888* D1Minimap_pixels(
    const D1Minimap* minimap
)
{
    return minimap->pixels.data();
}

uint16_t D1Minimap_width(
    const D1Minimap* minimap
)
{
    return minimap->width;
}

uint16_t D1Minimap_height(
    const D1Minimap* minimap
)
{
    return minimap->height;
}
