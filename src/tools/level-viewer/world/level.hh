#pragma once

#include "world/building.hh"
#include "world/map.hh"
#include "world/material.hh"
#include "world/minimap.hh"

#include <filesystem>

// -----------------------------------------------------------------------------

class Level
{
public:

    Level(const std::filesystem::path& dvdFilePath);

    const std::string& name() const;

    const std::shared_ptr<Map>& map() const;

    const std::shared_ptr<Minimap>& minimap() const;

    const std::vector<std::shared_ptr<Building>>& buildings() const;

    const std::vector<std::shared_ptr<Door>>& specialDoors() const;

    const std::vector<std::shared_ptr<MaterialZone>>& materialZones() const;

private:

    std::string m_name;
    std::shared_ptr<Map> m_map;
    std::shared_ptr<Minimap> m_minimap;
    std::vector<std::shared_ptr<Building>> m_buildings;
    std::vector<std::shared_ptr<Door>> m_specialDoors;
    std::vector<std::shared_ptr<MaterialZone>> m_materialZones;
};
