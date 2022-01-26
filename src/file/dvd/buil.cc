#include "file/dvd/buil.hh"

#include <bitset>
#include <iomanip>
#include <iostream>

// -----------------------------------------------------------------------------

std::vector<std::shared_ptr<Building>> parseBuilSector(
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
            std::vector<Coord2d> outlineCoords;
            std::vector<Coord3d> entryCoords;

            // 1

            auto doorType = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

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

            auto unknownByte07 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

            auto unknownByte08 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

            auto unknownByte09 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

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

            // What is this last u16? Padding?
            auto unknownWord__ = *reinterpret_cast<const uint16_t*>(currentByte);
            currentByte += sizeof(uint16_t);

            doors.push_back(std::make_shared<Door>(
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
                unknownByte09
            ));
        }

        buildings.push_back(std::make_shared<Building>(
            buildingUnkWord00,
            characterIds,
            doors
        ));
    }

    auto numSpecialDoors = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    auto unknownDataBegin = currentByte;
    auto unknownDataEnd = endOfData;
    auto bytesLeft = unknownDataEnd - unknownDataBegin;

    return buildings;
}
