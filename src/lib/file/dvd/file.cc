extern "C" {
#include "lib/file/dvd/bgnd.h"
#include "lib/file/dvd/file.h"
#include "lib/file/dvd/sector.h"
#include "lib/level/map.h"
#include "lib/level/minimap.h"
}

#include "lib/common/log.hh"

// TODO: This is dumb, but fixes a build error.
namespace {
#include <mio/mio.hpp>
}

#include <filesystem>

struct D1DvdFile
{
    std::filesystem::path path;

    std::string levelName = "";

    D1Map*     map     = nullptr;
    D1Minimap* minimap = nullptr;
};

#pragma pack(push, 1)
struct DvdSectorHeader
{
    D1DvdSectorId sectorId;
    uint32_t sectorDataSize;
};
#pragma pack(pop)

static_assert(sizeof(DvdSectorHeader) == 8);

// -----------------------------------------------------------------------------

D1DvdFile* D1DvdFile_newFromFile(
    const char* path
)
{
    auto file = new D1DvdFile;

    file->path = path;
    file->levelName = file->path.stem().string();

    mio::mmap_source memmap;
    std::error_code errorCode;
    memmap.map(path, errorCode);
    if (errorCode)
    {
        Log::fatal() << "Failed to load '" << path << "'\n" << std::flush;
    }

    auto fileSize   = std::filesystem::file_size(path);
    auto fileBegin  = reinterpret_cast<const uint8_t*>(memmap.data());
    auto fileEnd    = fileBegin + fileSize;

    auto currentByte = fileBegin;
    while (currentByte < fileEnd)
    {
        auto sectorHeader = reinterpret_cast<const DvdSectorHeader*>(currentByte);
        auto sectorData   = currentByte + sizeof(DvdSectorHeader);

        switch (sectorHeader->sectorId)
        {
        case D1DvdSectorBgnd:
            Log::debug() << "Loading " << file->levelName << " sector BGND\n" << std::flush;
            file->minimap = d1_parseDvdBgndSectorData(
                sectorData,
                sectorHeader->sectorDataSize
            );
            break;
        default:
            Log::warning()
                << "Skipping "
                << file->levelName
                << " sector "
                << D1DvdSectorId_toString(sectorHeader->sectorId)
                << "\n"
                << std::flush;
            break;
        }

        currentByte += sizeof(DvdSectorHeader) + sectorHeader->sectorDataSize;
    }
     
    return file;
}

void D1DvdFile_free(
    D1DvdFile* file
)
{
    D1Minimap_free(file->minimap);
    delete file;
}

D1Minimap* D1DvdFile_minimap(
    D1DvdFile* file
)
{
    return file->minimap;
}
