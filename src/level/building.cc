#include "level/building.hh"

// -----------------------------------------------------------------------------

Building::Building(
    uint16_t unknownWord00,
    const std::vector<uint16_t>& characterIds,
    const std::vector<std::shared_ptr<Door>>& doors
)
    : m_unknownWord00(unknownWord00)
    , m_characterIds(characterIds)
    , m_doors(doors)
{
}

uint16_t Building::unknownWord00() const
{
    return m_unknownWord00;
}

const std::vector<uint16_t>& Building::characterIds() const
{
    return m_characterIds;
}

const std::vector<std::shared_ptr<Door>>& Building::doors() const
{
    return m_doors;
}
