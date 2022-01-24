#pragma once

#include "level/map.hh"
#include "level/minimap.hh"

#include <filesystem>

// -----------------------------------------------------------------------------

class Level
{
public:

    Level(const std::filesystem::path& dvdFilePath);

    const std::string& name() const;

    const std::shared_ptr<Map>& map() const;

    const std::shared_ptr<Minimap>& minimap() const;

private:

    std::string m_name;
    std::shared_ptr<Map> m_map;
    std::shared_ptr<Minimap> m_minimap;
};
