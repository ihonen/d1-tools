#pragma once

#include <filesystem>

// -----------------------------------------------------------------------------

class Map;

// -----------------------------------------------------------------------------

class DvmFile
{
public:

    DvmFile(const std::filesystem::path& path);

    const std::shared_ptr<Map>& map() const;

private:

    std::filesystem::path m_path;

    std::string m_levelName;

    std::shared_ptr<Map> m_map;
};
