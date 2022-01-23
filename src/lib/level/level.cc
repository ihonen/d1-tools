extern "C" {
#include "lib/file/dvd/file.h"
#include "lib/file/dvm/file.h"
#include "lib/level/map.h"
#include "lib/level/minimap.h"
#include "lib/level/level.h"
}

#include "lib/common/log.hh"

// This fixes a build error. ._.
namespace {
#include <mio/mio.hpp>
}

#include <filesystem>

// -----------------------------------------------------------------------------

struct D1Level
{
    std::string name;

    D1Map*     map     = nullptr;
    D1Minimap* minimap = nullptr;
};

// -----------------------------------------------------------------------------

D1Level* D1Level_newFromDvdFile(
    const char* path
)
{
    auto dvdPath = std::filesystem::path(path);
    auto dvmPath = dvdPath;
    dvmPath.replace_extension(".dvm");

    auto dvdFile = D1DvdFile_newFromFile(dvdPath.string().c_str());
    auto dvmFile = D1DvmFile_newFromFile(dvmPath.string().c_str());

    auto level = new D1Level;
    level->name = dvdPath.stem().string();
    level->map = D1DvmFile_stealMap(dvmFile);
    level->minimap = D1DvdFile_stealMinimap(dvdFile);

    D1DvdFile_free(dvdFile);
    D1DvmFile_free(dvmFile);

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
