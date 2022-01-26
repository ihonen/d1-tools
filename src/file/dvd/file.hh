#pragma once

#include "level/building.hh"

#include <filesystem>

// -----------------------------------------------------------------------------

class Minimap;

// -----------------------------------------------------------------------------

class DvdFile
{
public:

    DvdFile(const std::filesystem::path& path);

    const std::shared_ptr<Minimap>& minimap() const;

    const std::vector<std::shared_ptr<Building>>& buildings() const;

private:

    std::filesystem::path m_path;

    std::string m_levelName;

    std::shared_ptr<Minimap> m_minimap;

    std::vector<std::shared_ptr<Building>> m_buildings;
};
