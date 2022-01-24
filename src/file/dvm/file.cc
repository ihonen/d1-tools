extern "C" {
#include "common/bzip2.h"
#include "file/dvm/file.h"
#include "image/pixel.h"
#include "level/map.h"
}

#include "common/log.hh"

#include <mio/mio.hpp>

#include <string>

// -----------------------------------------------------------------------------

struct D1DvmFile
{
    D1Map* map = nullptr;
};

// -----------------------------------------------------------------------------

D1DvmFile* D1DvmFile_newFromFile(
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

    auto width = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    auto height = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    auto compressionType = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    auto compressedSize = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    auto numPixels = width * height;
    unsigned decompressedDataSize = numPixels * sizeof(Bgr565);
    auto bgr565Pixels = new Bgr565[numPixels];

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

    auto pixels = new Bgr888[numPixels];

    for (size_t i = 0; i < numPixels; ++i)
    {
        bgr565_to_bgr888(&bgr565Pixels[i], &pixels[i]);
    }

    auto file = new D1DvmFile;
    file->map = D1Map_new(
        width,
        height,
        pixels
    );

    delete[] bgr565Pixels;
    delete[] pixels;

    return file;
}

void D1DvmFile_free(
    D1DvmFile* file
)
{
    D1Map_free(file->map);
    delete file;
}

D1Map* D1DvmFile_stealMap(
    D1DvmFile* file
)
{
    auto map = file->map;
    file->map = nullptr;
    return map;
}
