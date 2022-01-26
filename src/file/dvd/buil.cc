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

    std::cout << "version = " << version << "\n";

    auto numBuildings = *reinterpret_cast<const uint16_t*>(currentByte);
    currentByte += sizeof(uint16_t);

    std::cout << "numBuildings = " << numBuildings << "\n";

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
            std::vector<Coord> outlineCoords;
            Coord frontCoord;
            Coord onCoord;
            Coord inCoord;

            // 1
            {
                auto doorUnkByte00 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte01 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte02 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte03 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte04 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte05 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte06 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte07 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte08 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto doorUnkByte09 = *reinterpret_cast<const uint8_t*>(currentByte);
                currentByte += sizeof(uint8_t);

                auto numCoords = *reinterpret_cast<const uint16_t*>(currentByte);
                currentByte += sizeof(uint16_t);

                for (size_t iCoord = 0; iCoord < numCoords; ++iCoord)
                {
                    auto coord = *reinterpret_cast<const Coord*>(currentByte);
                    currentByte += sizeof(Coord);

                    outlineCoords.push_back(coord);
                }
            }

            // 2
            {
                auto idPoints = *reinterpret_cast<const uint16_t*>(currentByte);
                currentByte += sizeof(uint16_t);

                auto coord = *reinterpret_cast<const Coord*>(currentByte);
                currentByte += sizeof(Coord);

                auto doorUnkWord00 = *reinterpret_cast<const uint16_t*>(currentByte);
                currentByte += sizeof(uint16_t);

                auto doorUnkWord01 = *reinterpret_cast<const uint16_t*>(currentByte);
                currentByte += sizeof(uint16_t);

                frontCoord = coord;
            }

            // 3
            {
                auto coord = *reinterpret_cast<const Coord*>(currentByte);
                currentByte += sizeof(Coord);

                auto doorUnkWord02 = *reinterpret_cast<const uint16_t*>(currentByte);
                currentByte += sizeof(uint16_t);

                auto door3UnkWord03 = *reinterpret_cast<const uint16_t*>(currentByte);
                currentByte += sizeof(uint16_t);

                onCoord = coord;
            }

            // 4
            {
                auto coord = *reinterpret_cast<const Coord*>(currentByte);
                currentByte += sizeof(Coord);

                auto door4UnkWord04 = *reinterpret_cast<const uint16_t*>(currentByte);
                currentByte += sizeof(uint16_t);

                auto door4UnkWord05 = *reinterpret_cast<const uint16_t*>(currentByte);
                currentByte += sizeof(uint16_t);

                inCoord = coord;
            }

            // Experiment:
            auto unknownWord = *reinterpret_cast<const uint16_t*>(currentByte);
            currentByte += sizeof(uint16_t);

            doors.push_back(std::make_shared<Door>(
                outlineCoords,
                frontCoord,
                onCoord,
                inCoord
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
