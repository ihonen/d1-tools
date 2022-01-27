#include "file/dvd/buil.hh"

#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>

// -----------------------------------------------------------------------------

namespace
{

    std::shared_ptr<Door> parseDoorEntry(const uint8_t* entryBegin, size_t* entrySizeOut)
    {
        std::vector<Coord2d> outlineCoords;
        std::vector<Coord3d> entryCoords;

        auto currentByte = entryBegin;

        auto doorType = *reinterpret_cast<const Door::Type*>(currentByte);
        currentByte += sizeof(Door::Type);

        auto unknownByte01 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);

        auto locked = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);

        auto lockPickable = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);

        auto unknownByte04 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);

        auto unknownByte05 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);

        auto unknownByte06 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        assert(doorType == Door::Type::Normal ? unknownByte06 == 0x00 : true);

        auto unknownByte07 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        assert(doorType == Door::Type::Normal ? unknownByte07 == 0x00 : true);

        auto unknownByte08 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        assert(doorType == Door::Type::Normal ? unknownByte08 == 0x00 : true);

        auto unknownByte09 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        assert(doorType == Door::Type::Normal ? unknownByte09 == 0x00 : true);

        auto numOutlineCoords = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

        for (size_t iCoord = 0; iCoord < numOutlineCoords; ++iCoord)
        {
            outlineCoords.push_back(*reinterpret_cast<const Coord2d*>(currentByte));
            currentByte += sizeof(Coord2d);
        }

        auto numEntryCoords = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);
        assert(numEntryCoords == 3);

        for (size_t iCoord = 0; iCoord < numEntryCoords; ++iCoord)
        {
            entryCoords.push_back(*reinterpret_cast<const Coord3d*>(currentByte));
            currentByte += sizeof(Coord3d);
        }

        auto unknownWord00 = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

        uint16_t unknownByte10 = 0x00;
        uint16_t unknownByte11 = 0x00;
        if (unknownWord00 != 0xffff)
        {
            unknownByte10 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

            unknownByte11 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);
        }

        *entrySizeOut = currentByte - entryBegin;

        return std::make_shared<Door>(
            outlineCoords,
            entryCoords,
            doorType,
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
    auto endOfData = firstByteOfData + dataSize;

    auto version = *reinterpret_cast<const uint32_t*>(currentByte);
    currentByte += sizeof(uint32_t);

    assert(version == 4);

    auto numBuildings = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    for (size_t iBuilding = 0; iBuilding < numBuildings; ++iBuilding)
    {
        std::vector<uint16_t> characterIds;
        std::vector<std::shared_ptr<Door>> doors;

        auto buildingUnkByte00 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        
        auto buildingUnkByte01 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        assert(buildingUnkByte01 == 0x00);

        auto numCharacters = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

        for (size_t iCharacter = 0; iCharacter < numCharacters; ++iCharacter)
        {
            auto characterId = *reinterpret_cast<const uint16_t*>(currentByte);
            currentByte += sizeof(uint16_t);

            characterIds.push_back(characterId);
        }

        auto numDoors = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

        for (size_t iDoor = 0; iDoor < numDoors; ++iDoor)
        {
            size_t entrySize;
            auto door = parseDoorEntry(currentByte, &entrySize);
            doors.push_back(door);
            currentByte += entrySize;
        }

        buildings.push_back(std::make_shared<Building>(
            buildingUnkByte00,
            buildingUnkByte01,
            characterIds,
            doors
        ));
    }

    std::vector<std::shared_ptr<Door>> specialDoors;

    {
        auto numSpecialDoors = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

        for (size_t iSpecialDoor = 0; iSpecialDoor < numSpecialDoors; ++iSpecialDoor)
        {
            size_t entrySize;
            auto door = parseDoorEntry(currentByte, &entrySize);
            specialDoors.push_back(door);
            currentByte += entrySize;
        }
    }

    assert(currentByte == endOfData);

    return {buildings, specialDoors};
}
