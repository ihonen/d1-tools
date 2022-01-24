#include "common/log.hh"
#include "file/dvd/file.hh"
#include "file/dvm/file.hh"
#include "level/level.hh"
#include "level/map.hh"
#include "level/minimap.hh"

// This fixes a build error. ._.
namespace {
#include <mio/mio.hpp>
}

#include <filesystem>

// -----------------------------------------------------------------------------

Level::Level(const std::filesystem::path& dvdFilePath)
{
    auto dvmFilePath = dvdFilePath;
    dvmFilePath.replace_extension(".dvm");

    auto dvdFile = DvdFile(dvdFilePath);
    auto dvmFile = DvmFile(dvmFilePath);

    m_name = dvdFilePath.stem().string();
    m_map = dvmFile.map();
    m_minimap = dvdFile.minimap();
}

const std::string& Level::name() const
{
    return m_name;
}

const std::shared_ptr<Map>& Level::map() const
{
    return m_map;
}

const std::shared_ptr<Minimap>& Level::minimap() const
{
    return m_minimap;
}
