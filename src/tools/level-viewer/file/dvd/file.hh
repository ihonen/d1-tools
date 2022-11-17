#pragma once

#include "world/building.hh"
#include "world/material.hh"

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

    const std::vector<std::shared_ptr<Door>>& specialDoors() const;

    const std::vector<std::shared_ptr<MaterialZone>>& materialZones() const;

private:

    std::filesystem::path m_path;

    std::string m_levelName;

    std::shared_ptr<Minimap> m_minimap;

    std::vector<std::shared_ptr<Building>> m_buildings;
    std::vector<std::shared_ptr<Door>> m_specialDoors;

    std::vector<std::shared_ptr<MaterialZone>> m_materialZones;
};
