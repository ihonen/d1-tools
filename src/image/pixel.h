#pragma once

#include <stdint.h>

// -----------------------------------------------------------------------------

#include "image/fwd.h"

// -----------------------------------------------------------------------------

#pragma pack(push, 1)
struct Bgr565
{
    uint16_t b: 5;
    uint16_t g: 6;
    uint16_t r: 5;
};

struct Bgr888
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
};
#pragma pack(pop)

// -----------------------------------------------------------------------------

void bgr565_to_bgr888(const Bgr565* bgr565_in, Bgr888* bgr888_out);

void bgr888_to_bgr565(const Bgr888* bgr888_in, Bgr565* bgr565_out);
