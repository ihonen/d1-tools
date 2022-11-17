#include "file/dvd/common.hh"
#include "file/dvd/mat.hh"

#include <cassert>
#include <iomanip>
#include <iostream>

// -----------------------------------------------------------------------------

std::vector<std::shared_ptr<MaterialZone>> parseMatSector(
    const std::string levelName,
    const uint8_t* firstByteOfData,
    uint32_t dataSize
)
{
    std::vector< std::shared_ptr<MaterialZone>> materialZones;

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

            auto zoneMaterialType      = consume<uint8_t>(&currentByte);
            uint16_t zoneUnknownWord00 = consume<uint16_t>(&currentByte);

            std::optional<uint8_t> zoneUnknownByte00;
            std::optional<uint8_t> zoneUnknownByte01;
            std::optional<uint8_t> zoneUnknownByte02;
            std::optional<uint8_t> zoneUnknownByte03;
            std::optional<uint8_t> zoneUnknownByte04;
            std::optional<uint8_t> zoneUnknownByte05;
            std::optional<uint8_t> zoneUnknownByte06;
            std::optional<uint32_t> zoneUnknownDword00;

            if (zoneMaterialType != 0x08)
            {
                zoneUnknownByte00 = consume<uint8_t>(&currentByte);
                zoneUnknownByte01 = consume<uint8_t>(&currentByte);
                zoneUnknownByte02 = consume<uint8_t>(&currentByte);
                zoneUnknownByte03 = consume<uint8_t>(&currentByte);
                zoneUnknownByte04 = consume<uint8_t>(&currentByte);
                zoneUnknownByte05 = consume<uint8_t>(&currentByte);
                zoneUnknownByte06 = consume<uint8_t>(&currentByte);
                zoneUnknownDword00 = consume<uint32_t>(&currentByte);
            }

            auto numCoords = consume<uint16_t>(&currentByte);
            for (auto k = 0; k < numCoords; ++k)
            {
                zoneOutlineCoords.push_back(consume<Coord2d>(&currentByte));
            }

            materialZones.push_back(std::make_shared<MaterialZone>(
                static_cast<MaterialZone::Type>(zoneMaterialType),
                i + 1,
                zoneOutlineCoords,
                zoneUnknownWord00,
                zoneUnknownByte00,
                zoneUnknownByte01,
                zoneUnknownByte02,
                zoneUnknownByte03,
                zoneUnknownByte04,
                zoneUnknownByte05,
                zoneUnknownByte06,
                zoneUnknownDword00
            ));
        }
    }

    return materialZones;
}
