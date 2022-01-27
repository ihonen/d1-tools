#include "file/dvd/buil.hh"
#include "file/dvd/common.hh"

#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>

// -----------------------------------------------------------------------------

namespace
{

    std::shared_ptr<Door> consumeDoorEntry(const uint8_t** currentByte)
    {
        std::vector<Coord2d> outlineCoords;
        std::vector<Coord3d> entryCoords;

        auto doorType         = consume<uint8_t>(currentByte);
        auto unknownByte01    = consume<uint8_t>(currentByte);
        auto locked           = consume<uint8_t>(currentByte);
        auto lockPickable     = consume<uint8_t>(currentByte);
        auto unknownByte04    = consume<uint8_t>(currentByte);
        auto unknownByte05    = consume<uint8_t>(currentByte);
        auto unknownByte06    = consume<uint8_t>(currentByte);
        auto unknownByte07    = consume<uint8_t>(currentByte);
        auto unknownByte08    = consume<uint8_t>(currentByte);
        auto unknownByte09    = consume<uint8_t>(currentByte);
        auto numOutlineCoords = consume<uint16_t>(currentByte);

        for (auto i = 0; i < numOutlineCoords; ++i)
        {
            outlineCoords.push_back(consume<Coord2d>(currentByte));
        }

        auto numEntryCoords = consume<uint16_t>(currentByte);
        assert(numEntryCoords == 3);

        for (auto i = 0; i < numEntryCoords; ++i)
        {
            entryCoords.push_back(consume<Coord3d>(currentByte));
        }

        auto unknownWord00 = consume<uint16_t>(currentByte);
        auto unknownByte10 = (unknownWord00 != 0xffff) ? consume<uint8_t>(currentByte) : 0x00;
        auto unknownByte11 = (unknownWord00 != 0xffff) ? consume<uint8_t>(currentByte) : 0x00;

        return std::make_shared<Door>(
            outlineCoords,
            entryCoords,
            static_cast<Door::Type>(doorType),
            unknownByte01,
            locked,
            lockPickable,
            unknownByte04,
            unknownByte05,
            unknownByte06,
            unknownByte07,
            unknownByte08,
            unknownByte09,
            unknownWord00,
            unknownByte10,
            unknownByte11
        );
    }
}

// -----------------------------------------------------------------------------

std::pair<std::vector<std::shared_ptr<Building>>, std::vector<std::shared_ptr<Door>>>
parseBuilSector(
    const std::string levelName,
    const uint8_t* firstByteOfData,
    uint32_t dataSize
)
{
    std::vector<std::shared_ptr<Building>> buildings;

    auto currentByte = firstByteOfData;
    auto endOfData   = firstByteOfData + dataSize;

    auto version = consume<uint32_t>(&currentByte);
    assert(version == 4);

    auto numBuildings = consume<uint16_t>(&currentByte);

    {
        for (size_t i = 0; i < numBuildings; ++i)
        {
            std::vector<uint16_t> characterIds;
            std::vector<std::shared_ptr<Door>> doors;

            auto unknownByte00 = consume<uint8_t>(&currentByte);
            auto unknownByte01 = consume<uint8_t>(&currentByte);
            auto numCharacters = consume<uint16_t>(&currentByte);

            for (size_t j = 0; j < numCharacters; ++j)
            {
                characterIds.push_back(consume<uint16_t>(&currentByte));
            }

            auto numDoors = consume<uint16_t>(&currentByte);

            for (size_t j = 0; j < numDoors; ++j)
            {
                doors.push_back(consumeDoorEntry(&currentByte));
            }

            assert(unknownByte01 == 0x00);

            buildings.push_back(std::make_shared<Building>(
                unknownByte00,
                unknownByte01,
                characterIds,
                doors
            ));
        }
    }

    std::vector<std::shared_ptr<Door>> specialDoors;

    {
        auto numSpecialDoors = consume<uint16_t>(&currentByte);

        for (size_t i = 0; i < numSpecialDoors; ++i)
        {
            specialDoors.push_back(consumeDoorEntry(&currentByte));
        }
    }

    assert(currentByte == endOfData);

    return {buildings, specialDoors};
}
