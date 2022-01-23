extern "C" {
#include "lib/level/map.h"
#include "lib/level/minimap.h"
#include "lib/level/level.h"
}

#include "lib/common/log.hh"

// TODO: This is dumb, but fixes a build error.
namespace {
#include <mio/mio.hpp>
}

#include <filesystem>

// -----------------------------------------------------------------------------

enum DvdSectorId : uint32_t
{
    DvdSectorAi    = 0x20204941,
    DvdSectorBgnd  = 0x444E4742,
    DvdSectorBond  = 0x444E4F42,
    DvdSectorBuil  = 0x4C495542,
    DvdSectorCart  = 0x54524143,
    DvdSectorDlgs  = 0x53474C44,
    DvdSectorElem  = 0x4D454C45,
    DvdSectorFxbk  = 0x4B425846,
    DvdSectorJump  = 0x504D554A,
    DvdSectorLift  = 0x5446494C,
    DvdSectorMask  = 0x4B53414D,
    DvdSectorMat   = 0x2054414D,
    DvdSectorMisc  = 0x4353494D,
    DvdSectorMove  = 0x45564F4D,
    DvdSectorMsic  = 0x4349534D,
    DvdSectorPat   = 0x20544150,
    DvdSectorScrp  = 0x50524353,
    DvdSectorSght  = 0x54484753,
    DvdSectorSnd   = 0x20444E53,
    DvdSectorWays  = 0x53594157,
};

static std::string dvdSectorIdToString(
    DvdSectorId id
)
{
    switch (id)
    {
    case DvdSectorAi:   return "AI";
    case DvdSectorBgnd: return "BGND";
    case DvdSectorBond: return "BOND";
    case DvdSectorBuil: return "BUIL";
    case DvdSectorCart: return "CART";
    case DvdSectorDlgs: return "DLGS";
    case DvdSectorElem: return "ELEM";
    case DvdSectorFxbk: return "FXBK";
    case DvdSectorJump: return "JUMP";
    case DvdSectorLift: return "LIFT";
    case DvdSectorMask: return "MASK";
    case DvdSectorMat:  return "MAT";
    case DvdSectorMisc: return "MISC";
    case DvdSectorMove: return "MOVE";
    case DvdSectorMsic: return "MSIC";
    case DvdSectorPat:  return "PAT";
    case DvdSectorScrp: return "SCRP";
    case DvdSectorSght: return "SGHT";
    case DvdSectorSnd:  return "SND";
    case DvdSectorWays: return "WAYS";
    }

    return "<INVALID>";
}

struct D1Level
{
    std::string name;

    D1Map*     map     = nullptr;
    D1Minimap* minimap = nullptr;
};

#pragma pack(push, 1)
struct DvdSectorHeader
{
    DvdSectorId sectorId;
    uint32_t sectorDataSize;
};
#pragma pack(pop)

static_assert(sizeof(DvdSectorHeader) == 8);

// -----------------------------------------------------------------------------

D1Level* D1Level_newFromDvdFile(
    const char* path
)
{
    auto level = new D1Level;

    level->name = std::filesystem::path(path).stem().string();

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
        case DvdSectorBgnd:
            Log::debug() << "Loading " << level->name << " sector BGND\n" << std::flush;
            level->minimap = D1Minimap_newFromBgndSector(
                sectorData,
                sectorHeader->sectorDataSize,
                level
            );
            break;
        default:
            Log::warning()
                << "Skipping "
                << level->name
                << " sector "
                << dvdSectorIdToString(sectorHeader->sectorId)
                << "\n"
                << std::flush;
            break;
        }

        currentByte += sizeof(DvdSectorHeader) + sectorHeader->sectorDataSize;
    }

    std::filesystem::path dvdFile(path);
    auto dvmFile = dvdFile;
    dvmFile.replace_extension(".dvm");

    level->map = D1Map_newFromDvmFile(
        dvmFile.string().c_str(),
        level
    );
     
    return level;
}

void D1Level_free(
    D1Level* level
)
{
    D1Map_free(level->map);
    D1Minimap_free(level->minimap);
    delete level;
}

const char* D1Level_name(
    D1Level* level
)
{
    return level->name.c_str();
}

D1Map* D1Level_map(
    D1Level* level
)
{
    return level->map;
}


D1Minimap* D1Level_minimap(
    D1Level* level
)
{
    return level->minimap;
}
