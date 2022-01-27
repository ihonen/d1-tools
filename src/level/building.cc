#include "level/building.hh"

// -----------------------------------------------------------------------------

Building::Building(
    uint8_t unknownByte00,
    uint8_t unknownByte01,
    const std::vector<uint16_t>& characterIds,
    const std::vector<std::shared_ptr<Door>>& doors
)
    : m_unknownByte00(unknownByte00)
    , m_unknownByte01(unknownByte01)
    , m_characterIds(characterIds)
    , m_doors(doors)
{
    for (const auto& door : m_doors)
    {
        door->setParent(this);
    }
}

uint8_t Building::unknownByte00() const
{
    return m_unknownByte00;
}

uint8_t Building::unknownByte01() const
{
    return m_unknownByte01;
}

const std::vector<uint16_t>& Building::characterIds() const
{
    return m_characterIds;
}

const std::vector<std::shared_ptr<Door>>& Building::doors() const
{
    return m_doors;
}
