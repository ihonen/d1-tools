extern "C" {
#include "file/dvd/bgnd.h"
#include "file/dvd/file.h"
#include "file/dvd/sector.h"
#include "level/map.h"
#include "level/minimap.h"
}

#include "common/log.hh"

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

D1Minimap* D1DvdFile_stealMinimap(
    D1DvdFile* file
)
{
    auto minimap = file->minimap;
    file->minimap = nullptr;
    return minimap;
}
