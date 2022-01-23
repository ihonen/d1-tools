extern "C" {
#include "lib/common/bzip2.h"
#include "lib/image/pixel.h"
#include "lib/level/level.h"
#include "lib/level/map.h"
}

#include "lib/common/log.hh"

// TODO: This is dumb, but fixes a build error.
namespace {
#include <mio/mio.hpp>
}

#include <vector>

// -----------------------------------------------------------------------------

struct D1Map
{
    uint32_t version         = 0;
    uint16_t filenameLen     = 0;
    std::string fileName     = "";
    uint16_t width           = 0;
    uint16_t height          = 0;
    uint32_t compressionType = 0;
    uint32_t compressedSize  = 0;

    std::vector<Bgr888> pixels;
};

// -----------------------------------------------------------------------------

D1Map* D1Map_newFromDvmFile(
    const char* path
)
{
    mio::mmap_source memmap;
    std::error_code errorCode;
    memmap.map(path, errorCode);
    if (errorCode)
    {
        Log::fatal() << "Failed to load '" << path << "'\n" << std::flush;
        abort();
    }

    auto fileSize    = std::filesystem::file_size(path);
    auto fileBegin   = reinterpret_cast<const uint8_t*>(memmap.data());
    auto fileEnd     = fileBegin + fileSize;
    auto currentByte = fileBegin;

    auto map = new D1Map;

    map->width = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    map->height = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    map->compressionType = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    map->compressedSize = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    auto numPixels = map->width * map->height;

    unsigned decompressedDataSize = numPixels * sizeof(Bgr565);
    auto bgr565Pixels = new Bgr565[numPixels];

    bzip2Decompress(
        bgr565Pixels,
        &decompressedDataSize,
        currentByte,
        map->compressedSize
    );

    auto numPixels2 = decompressedDataSize / sizeof(Bgr565);

    if (numPixels != numPixels2)
    {
        Log::fatal() << "Bzip2 decompression failed\n" << std::flush;
        abort();
    }

    map->pixels.resize(numPixels);
    for (size_t i = 0; i < numPixels; ++i)
    {
        auto& bgr565Pixel = bgr565Pixels[i];
        auto& bgr888Pixel = map->pixels[i];

        bgr565_to_bgr888(&bgr565Pixel, &bgr888Pixel);
    }

    delete[] bgr565Pixels;

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
