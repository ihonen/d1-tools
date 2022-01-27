#pragma once

#include <cstdint>
#include <vector>

// -----------------------------------------------------------------------------

struct Bgr888;

// -----------------------------------------------------------------------------

class Minimap
{
public:

    Minimap(uint16_t width, uint16_t height, const std::vector<Bgr888>& pixels);

    uint16_t width() const;

    uint16_t height() const;

    const Bgr888* pixels() const;

private:

    uint16_t m_width = 0;
    uint16_t m_height = 0;
    std::vector<Bgr888> m_pixels;
};
