#include "common/bzip2.hh"
#include "common/log.hh"
#include "image/pixel.hh"
#include "level/level.hh"
#include "level/minimap.hh"

#include <vector>

// -----------------------------------------------------------------------------

Minimap::Minimap(uint16_t width, uint16_t height, const std::vector<Bgr888>& pixels)
    : m_width(width)
    , m_height(height)
    , m_pixels(pixels)
{
}

uint16_t Minimap::width() const
{
    return m_width;
}

uint16_t Minimap::height() const
{
    return m_height;
}

const Bgr888* Minimap::pixels() const
{
    return m_pixels.data();
}
