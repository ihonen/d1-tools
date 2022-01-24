#pragma once

#include <filesystem>

// -----------------------------------------------------------------------------

class Minimap;

// -----------------------------------------------------------------------------

class DvdFile
{
public:

    DvdFile(const std::filesystem::path& path);

    const std::shared_ptr<Minimap>& minimap() const;

private:

    std::filesystem::path m_path;

    std::string m_levelName;

    std::shared_ptr<Minimap> m_minimap;
};
