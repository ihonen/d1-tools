#include "file/dvd/common.hh"
#include "file/dvd/mat.hh"

#include <cassert>
#include <iomanip>
#include <iostream>

// -----------------------------------------------------------------------------

std::vector<std::shared_ptr<Material>> parseMatSector(
    const std::string levelName,
    const uint8_t* firstByteOfData,
    uint32_t dataSize
)
{
    std::vector< std::shared_ptr<Material>> materials;

    auto endOfData = firstByteOfData + dataSize;
    auto currentByte = firstByteOfData;

    auto version = consume<uint32_t>(&currentByte);
    assert(version == 4);

    auto numSections = consume<uint16_t>(&currentByte);

    for (auto i = 0; i < numSections; ++i)
    {
        auto unknownByte00    = consume<uint8_t>(&currentByte);
        auto unknownByte01    = consume<uint8_t>(&currentByte);
        auto numMaterialZones = consume<uint16_t>(&currentByte);

        for (auto j = 0; j < numMaterialZones; ++j)
        {
            std::vector<Coord2d> zoneOutlineCoords;

            auto zoneMaterialType = consume<uint8_t>(&currentByte);

            if (zoneMaterialType == 0x08)
            {
                for (auto k = 0; k < 2; ++k)
                {
                    consume<uint8_t>(&currentByte);
                }
            }
            else
            {
                for (auto k = 0; k < 13; ++k)
                {
                    consume<uint8_t>(&currentByte);
                }
            }

            auto numCoords = consume<uint16_t>(&currentByte);
            for (auto k = 0; k < numCoords; ++k)
            {
                zoneOutlineCoords.push_back(consume<Coord2d>(&currentByte));
            }

            materials.push_back(std::make_shared<Material>(zoneOutlineCoords, zoneMaterialType));
        }
    }

    return materials;
}
