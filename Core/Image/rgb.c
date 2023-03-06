#include "rgb.h"

#include <assert.h>

// ---------------------------------------------------------

void bgr565_to_bgr888(const Bgr565* src, Bgr888* dest, size_t num_pixels)
{
    const Bgr565* const src_end  = src  + num_pixels;
    const Bgr888* const dest_end = dest + num_pixels;

    for (; src < src_end; ++src, ++dest)
    {
        dest->b = (src->b * 527 + 23) >> 6;
        dest->g = (src->g * 259 + 33) >> 6;
        dest->r = (src->r * 527 + 23) >> 6;
    }

    assert(src == src_end);
    assert(dest == dest_end);
}

void bgr888_to_bgr565(const Bgr888* src, Bgr565* dest, size_t num_pixels)
{
    const Bgr888* const src_end  = src  + num_pixels;
    const Bgr565* const dest_end = dest + num_pixels;

    for (; src < src_end; ++src, ++dest)
    {
        dest->b = (src->b * 249 + 1014 ) >> 11;
        dest->g = (src->g * 253 +  505 ) >> 10;
        dest->r = (src->r * 249 + 1014 ) >> 11;
    }

    assert(src == src_end);
    assert(dest == dest_end);
}

void bgr888_to_ppm(const Bgr888* src, size_t width, size_t height, FILE* out)
{
    // ASCII:
    // fprintf(out, "P3\n");
    // Binary:
    fprintf(out, "P6\n");
    fprintf(out, "%u, %u\n", (unsigned)width, (unsigned)height);
    fprintf(out, "255\n");

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            size_t offset = y * width + x;
            // ASCII:
            // fprintf(out, "% 3u % 3u % 3u\n", src[offset].r, src[offset].g, src[offset].b);
            // Binary:
            fwrite(&src[offset].r, sizeof(u8), 1, out);
            fwrite(&src[offset].g, sizeof(u8), 1, out);
            fwrite(&src[offset].b, sizeof(u8), 1, out);
        }
    }
}