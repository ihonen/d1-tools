#pragma once

#include "world/door.hh"
#include "world/worlditem.hh"

#include <memory>
#include <vector>

// -----------------------------------------------------------------------------

class Building
    : public WorldItem
{
public:

    Building(
        uint8_t unknownByte00,
        uint8_t unknownByte01,
        const std::vector<uint16_t>& characterIds,
        const std::vector<std::shared_ptr<Door>>& doors
    );

    uint8_t unknownByte00() const;
    uint8_t unknownByte01() const;

    const std::vector<uint16_t>& characterIds() const;

    const std::vector<std::shared_ptr<Door>>& doors() const;

private:

    uint8_t m_unknownByte00;
    uint8_t m_unknownByte01;
    std::vector<uint16_t> m_characterIds;
    std::vector<std::shared_ptr<Door>> m_doors;
};
