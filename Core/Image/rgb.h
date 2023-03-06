#pragma once

#include "Core/Util/typedef.h"

#include <stdint.h>
#include <stdio.h>

// ---------------------------------------------------------

#pragma pack(push, 1)
typedef struct
{
    u16 b: 5;
    u16 g: 6;
    u16 r: 5;
} Bgr565;

typedef struct
{
    u8 b;
    u8 g;
    u8 r;
} Bgr888;
#pragma pack(pop)

// ---------------------------------------------------------

void bgr565_to_bgr888(const Bgr565* src, Bgr888* dest, size_t num_pixels);
void bgr888_to_bgr565(const Bgr888* src, Bgr565* dest, size_t num_pixels);
void bgr888_to_ppm(const Bgr888* src, size_t width, size_t height, FILE* out);
