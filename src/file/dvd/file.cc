#include "common/log.hh"
#include "file/dvd/bgnd.hh"
#include "file/dvd/buil.hh"
#include "file/dvd/file.hh"
#include "file/dvd/sector.hh"
#include "level/map.hh"
#include "level/minimap.hh"

// TODO: This is dumb, but fixes a build error.
namespace {
#include <mio/mio.hpp>
}

// -----------------------------------------------------------------------------

#pragma pack(push, 1)
struct DvdSectorHeader
{
    DvdSector sectorId;
    uint32_t sectorDataSize;
};
#pragma pack(pop)

static_assert(sizeof(DvdSectorHeader) == 8);

// -----------------------------------------------------------------------------

DvdFile::DvdFile(const std::filesystem::path& path)
{
    m_path = path;
    m_levelName = m_path.stem().string();

    mio::mmap_source memmap;
    std::error_code errorCode;
    memmap.map(path.string(), errorCode);
    if (errorCode)
    {
        throw std::runtime_error("Failed to load " + path.string() + "\n");
    }

    auto fileSize = std::filesystem::file_size(path);
    auto fileBegin = reinterpret_cast<const uint8_t*>(memmap.data());
    auto fileEnd = fileBegin + fileSize;

    auto currentByte = fileBegin;
    while (currentByte < fileEnd)
    {
        auto sectorHeader = reinterpret_cast<const DvdSectorHeader*>(currentByte);
        auto sectorData = currentByte + sizeof(DvdSectorHeader);

        switch (sectorHeader->sectorId)
        {
        case DvdSector::Bgnd:
            Log::debug() << "Loading sector BGND\n" << std::flush;
            m_minimap = parseBgndSector(
                sectorData,
                sectorHeader->sectorDataSize
            );
            break;
        case DvdSector::Buil:
            Log::debug() << "Loading sector BUIL\n" << std::flush;
            std::tie(m_buildings, m_specialDoors) = parseBuilSector(
                m_levelName,
                sectorData,
                sectorHeader->sectorDataSize
            );
            break;
        default:
            Log::warning()
                << "Skipping sector "
                << DvdSector_toString(sectorHeader->sectorId)
                << "\n"
                << std::flush;
            break;
        }

        currentByte += sizeof(DvdSectorHeader) + sectorHeader->sectorDataSize;
    }
}

const std::shared_ptr<Minimap>& DvdFile::minimap() const
{
    return m_minimap;
}

const std::vector<std::shared_ptr<Building>>& DvdFile::buildings() const
{
    return m_buildings;
}

const std::vector<std::shared_ptr<Door>>& DvdFile::specialDoors() const
{
    return m_specialDoors;
}
