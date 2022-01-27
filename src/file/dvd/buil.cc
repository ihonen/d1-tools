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

        auto doorType = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);

        auto unknownByte01 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        //assert(unknownByte01 == 0x01);

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
        //assert(always_0x00_1 == 0x00);

        auto unknownByte07 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        //assert(always_0x00_2 == 0x00);

        auto unknownByte08 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        //assert(always_0x00_3 == 0x00);

        auto unknownByte09 = *reinterpret_cast<const uint8_t*>(currentByte);
        currentByte += sizeof(uint8_t);
        //assert(always_0x00_4 == 0x00);

        auto numOutlineCoords = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

        for (size_t iCoord = 0; iCoord < numOutlineCoords; ++iCoord)
        {
            outlineCoords.push_back(*reinterpret_cast<const Coord2d*>(currentByte));
            currentByte += sizeof(Coord2d);
        }

        auto numEntryCoords = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

        for (size_t iCoord = 0; iCoord < numEntryCoords; ++iCoord)
        {
            entryCoords.push_back(*reinterpret_cast<const Coord3d*>(currentByte));
            currentByte += sizeof(Coord3d);
        }

        auto unknownWord00 = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

        auto unknownWord01 = 0x0000;
        if (unknownWord00 != 0xffff)
        {
            unknownWord01 = *reinterpret_cast<const uint16_t*>(currentByte);
            currentByte += sizeof(uint16_t);
        }

        *entrySizeOut = currentByte - entryBegin;

        return std::make_shared<Door>(
            outlineCoords,
            entryCoords,
            doorType,
            locked,
            unknownByte01,
            lockPickable,
            unknownByte04,
            unknownByte05,
            unknownByte06,
            unknownByte07,
            unknownByte08,
            unknownByte09,
            unknownWord00,
            unknownWord01
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

    auto numBuildings = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    for (size_t iBuilding = 0; iBuilding < numBuildings; ++iBuilding)
    {
        std::vector<uint16_t> characterIds;
        std::vector<std::shared_ptr<Door>> doors;

        auto buildingUnkWord00 = *reinterpret_cast<const uint16_t*>(currentByte);
        currentByte += sizeof(uint16_t);

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
            buildingUnkWord00,
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
