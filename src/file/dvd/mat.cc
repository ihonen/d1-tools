#include "file/dvd/common.hh"
#include "file/dvd/mat.hh"

#include <cassert>
#include <iomanip>
#include <iostream>

// -----------------------------------------------------------------------------

std::vector<std::vector<Coord2d>> parseMatSector(
    const std::string levelName,
    const uint8_t* firstByteOfData,
    uint32_t dataSize
)
{
    std::vector<std::vector<Coord2d>> coordSets;

    auto endOfData = firstByteOfData + dataSize;
    auto currentByte = firstByteOfData;

    auto version = consume<uint32_t>(&currentByte);
    assert(version == 4);
    std::cout << "version = " << version << "\n";

    auto numSections = consume<uint16_t>(&currentByte);
    std::cout << "numSections = " << numSections << "\n";

    for (auto i = 0; i < numSections; ++i)
    {
        auto unknownWord00 = consume<uint16_t>(&currentByte);
        std::cout << "unknownWord00 = " << unknownWord00 << "\n";

        auto numEntries = consume<uint16_t>(&currentByte);
        std::cout << "numEntries = " << numEntries << "\n";

        for (auto j = 0; j < numEntries; ++j)
        {
            std::vector<Coord2d> coordSet;

            auto id = consume<uint8_t>(&currentByte);

            if (id == 0x08)
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
            std::cout << "numCoords = " << numCoords << "\n";
            for (auto k = 0; k < numCoords; ++k)
            {
                coordSet.push_back(consume<Coord2d>(&currentByte));
                std::cout << std::hex << std::setw(4) << std::setfill('0') << coordSet.back().x << ", " << std::setw(4) << coordSet.back().y << "\n";
            }
            coordSets.push_back(coordSet);
        }  
    }

    /*
    while (currentByte < endOfData)
    {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << int(consume<uint8_t>(&currentByte)) << "\n";
        //std::cout << int(consume<uint16_t>(&currentByte)) << "\n";
    }
    */

    return coordSets;
}
