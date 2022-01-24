extern "C" {
#include "common/bzip2.h"
#include "image/pixel.h"
#include "level/level.h"
#include "level/map.h"
}

#include "common/log.hh"

// TODO: This is dumb, but fixes a build error.
namespace {
#include <mio/mio.hpp>
}

#include <vector>

// -----------------------------------------------------------------------------

struct D1Map
{
    uint16_t width  = 0;
    uint16_t height = 0;

    std::vector<Bgr888> pixels;
};

// -----------------------------------------------------------------------------

D1Map* D1Map_new(
    uint16_t width,
    uint16_t height,
    const Bgr888* pixels
)
{
    auto map = new D1Map;
    map->width = width;
    map->height = height;
    map->pixels = std::vector<Bgr888>(
        pixels,
        pixels + width * height
    );

    return map;
}

void D1Map_free(
    D1Map* map
)
{
    delete map;
}

const Bgr888* D1Map_pixels(
    const D1Map* map
)
{
    return map->pixels.data();
}

uint16_t D1Map_width(
    const D1Map* map
)
{
    return map->width;
}

uint16_t D1Map_height(
    const D1Map* map
)
{
    return map->height;
}
