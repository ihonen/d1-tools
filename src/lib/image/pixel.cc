extern "C" {
#include "lib/image/pixel.h"
}

// -----------------------------------------------------------------------------

static_assert(sizeof(Bgr565) == 2);
static_assert(sizeof(Bgr888) == 3);

// -----------------------------------------------------------------------------

void bgr565_to_bgr888(
    const Bgr565* Bgr565In,
    Bgr888* Bgr888Out
)
{
    // There's some error in the conversion, apparently, so correct it.

    Bgr888Out->b = static_cast<uint8_t>((Bgr565In->b * 527 + 23) >> 6);
    Bgr888Out->b = Bgr888Out->b >= 251 ? 255 : Bgr888Out->b;

    Bgr888Out->g = static_cast<uint8_t>((Bgr565In->g * 259 + 33) >> 6);
    Bgr888Out->g = Bgr888Out->g >= 251 ? 255 : Bgr888Out->g;
    
    Bgr888Out->r = static_cast<uint8_t>((Bgr565In->r * 527 + 23) >> 6);
}

void bgr888_to_bgr565(
    const Bgr888* bgr888In,
    Bgr565* bgr565Out
)
{
    bgr565Out->b = static_cast<uint8_t>((bgr888In->b * 249 + 1014 ) >> 11);
    bgr565Out->g = static_cast<uint8_t>((bgr888In->g * 253 +  505 ) >> 10);
    bgr565Out->r = static_cast<uint8_t>((bgr888In->r * 249 + 1014 ) >> 11);
}
