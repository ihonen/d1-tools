#include "common/bzip2.hh"
#include "common/log.hh"
#include "file/dvd/bgnd.hh"
#include "image/pixel.hh"
#include "world/minimap.hh"

#include <string>

// -----------------------------------------------------------------------------

std::shared_ptr<Minimap> parseBgndSector(
    const uint8_t* firstByteOfData,
    uint32_t dataSize
)
{
    auto currentByte = firstByteOfData;

    auto version = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    auto filenameLen = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    auto fileName = std::string(
        reinterpret_cast<const char*>(currentByte),
        reinterpret_cast<const char*>(currentByte) + filenameLen
    );
    currentByte += filenameLen;

    auto width = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    auto height = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    auto compressionType = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    auto compressedSize = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);
    
    if (currentByte + compressedSize > firstByteOfData + dataSize)
    {
        Log::fatal() << "DVD sector BGND is malformed\n" << std::flush;
        abort();
    }

    auto numPixels = width * height;
    unsigned decompressedDataSize = numPixels * sizeof(Bgr565);
    Bgr565* bgr565Pixels = new Bgr565[numPixels];

    bzip2Decompress(
        bgr565Pixels,
        &decompressedDataSize,
        currentByte,
        compressedSize
    );

    auto numPixels2 = decompressedDataSize / sizeof(Bgr565);

    if (numPixels != numPixels2)
    {
        Log::fatal() << "DVD Sector BGND is malformed\n" << std::flush;
        abort();
    }

    auto bgr888Pixels = std::vector<Bgr888>(numPixels, {0, 0, 0});
    for (size_t i = 0; i < numPixels; ++i)
    {
        bgr565_to_bgr888(&bgr565Pixels[i], &bgr888Pixels[i]);
    }

    auto minimap = std::make_shared<Minimap>(width, height, bgr888Pixels);

    delete[] bgr565Pixels;

    return minimap;
}
