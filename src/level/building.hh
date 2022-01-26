#pragma once

#include "level/door.hh"
#include "level/worlditem.hh"

#include <memory>
#include <vector>

// -----------------------------------------------------------------------------

class Building
    : public WorldItem
{
public:

    Building(
        uint16_t unknownWord00,
        const std::vector<uint16_t>& characterIds,
        const std::vector<std::shared_ptr<Door>>& doors
    );

    uint16_t unknownWord00() const;

    const std::vector<uint16_t>& characterIds() const;

    const std::vector<std::shared_ptr<Door>>& doors() const;

private:

    uint16_t m_unknownWord00;
    std::vector<uint16_t> m_characterIds;
    std::vector<std::shared_ptr<Door>> m_doors;
};
