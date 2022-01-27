#include "common/bzip2.hh"
#include "common/log.hh"
#include "image/pixel.hh"
#include "world/level.hh"
#include "world/map.hh"

// TODO: This is dumb, but fixes a build error.
namespace {
#include <mio/mio.hpp>
}

// -----------------------------------------------------------------------------

Map::Map(uint16_t width, uint16_t height, const std::vector<Bgr888>& pixels)
    : m_width(width)
    , m_height(height)
    , m_pixels(pixels)
{
}

uint16_t Map::width() const
{
    return m_width;
}

uint16_t Map::height() const
{
    return m_height;
}

const Bgr888* Map::pixels() const
{
    return m_pixels.data();
}
