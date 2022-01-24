#include "common/bzip2.hh"
#include "common/log.hh"
#include "file/dvm/file.hh"
#include "image/pixel.hh"
#include "level/map.hh"

#include <mio/mio.hpp>

#include <string>

// -----------------------------------------------------------------------------

DvmFile::DvmFile(const std::filesystem::path& path)
{
    mio::mmap_source memmap;
    std::error_code errorCode;
    memmap.map(path.string(), errorCode);
    if (errorCode)
    {
        throw std::runtime_error("Failed to load " + path.string());
    }

    auto fileSize = std::filesystem::file_size(path);
    auto fileBegin = reinterpret_cast<const uint8_t*>(memmap.data());
    auto fileEnd = fileBegin + fileSize;
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
        throw std::runtime_error(path.string() + " is malformed");
    }

    auto bgr888Pixels = std::vector<Bgr888>(numPixels, {0, 0, 0});
    for (size_t i = 0; i < numPixels; ++i)
    {
        bgr565_to_bgr888(&bgr565Pixels[i], &bgr888Pixels[i]);
    }

    m_map = std::make_unique<Map>(width, height, bgr888Pixels);

    delete[] bgr565Pixels;
}

const std::shared_ptr<Map>& DvmFile::map() const
{
    return m_map;
}
