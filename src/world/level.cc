#include "common/log.hh"
#include "file/dvd/file.hh"
#include "file/dvm/file.hh"
#include "world/level.hh"
#include "world/map.hh"
#include "world/minimap.hh"

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
    m_buildings = dvdFile.buildings();
    m_specialDoors = dvdFile.specialDoors();
    m_materials = dvdFile.materials();
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

const std::vector<std::shared_ptr<Building>>& Level::buildings() const
{
    return m_buildings;
}

const std::vector<std::shared_ptr<Door>>& Level::specialDoors() const
{
    return m_specialDoors;
}

const std::vector<std::shared_ptr<Material>>& Level::materials() const
{
    return m_materials;
}
