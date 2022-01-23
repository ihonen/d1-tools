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

D1Minimap* D1Minimap_newFromBgndSector(
    const uint8_t* sectorDataBegin,
    uint32_t /*sectorDataSize*/
)
{
    auto minimap = new D1Minimap;
    
    auto currentByte = sectorDataBegin;

    minimap->version = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    minimap->filenameLen = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    minimap->fileName = std::string(
        reinterpret_cast<const char*>(currentByte),
        reinterpret_cast<const char*>(currentByte) + minimap->filenameLen
    );
    currentByte += minimap->filenameLen;

    minimap->width = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    minimap->height = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    minimap->compressionType = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    minimap->compressedSize = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    auto numPixels = minimap->width * minimap->height;

    unsigned decompressedDataSize = numPixels * sizeof(Bgr565);
    auto bgr565Pixels = new Bgr565[numPixels];

    bzip2Decompress(
        bgr565Pixels,
        &decompressedDataSize,
        currentByte,
        minimap->compressedSize
    );

    auto numPixels2 = decompressedDataSize / sizeof(Bgr565);

    if (numPixels != numPixels2)
    {
        Log::fatal() << "Bzip2 decompression failed\n" << std::flush;
        abort();
    }

    minimap->pixels.resize(numPixels);
    for (size_t i = 0; i < numPixels; ++i)
    {
        auto& bgr565Pixel = bgr565Pixels[i];
        auto& bgr888Pixel = minimap->pixels[i];

        bgr565_to_bgr888(&bgr565Pixel, &bgr888Pixel);
    }

    delete bgr565Pixels;

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
