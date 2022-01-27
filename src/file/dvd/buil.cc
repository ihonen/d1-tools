#include "file/dvd/buil.hh"

#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>

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
            std::vector<Coord2d> outlineCoords;
            std::vector<Coord3d> entryCoords;

            // 1

            auto doorType = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

            auto unknownByte01 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);
            assert(unknownByte01 == 0x01);

            auto locked = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

            auto lockPickable = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

            auto unknownByte04 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

            auto unknownByte05 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);

            auto always_0x00_1 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);
            assert(always_0x00_1 == 0x00);

            auto always_0x00_2 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);
            assert(always_0x00_2 == 0x00);

            auto always_0x00_3 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);
            assert(always_0x00_3 == 0x00);

            auto always_0x00_4 = *reinterpret_cast<const uint8_t*>(currentByte);
            currentByte += sizeof(uint8_t);
            assert(always_0x00_4 == 0x00);

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
                always_0x00_1,
                always_0x00_2,
                always_0x00_3,
                always_0x00_4
            ));
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

        auto unknownDataBegin = currentByte;
        auto unknownDataEnd = endOfData;
        auto bytesLeft = unknownDataEnd - unknownDataBegin;

    /*
        std::cout << "numSpecialDoors = " << numSpecialDoors << "\n";
        std::cout << "bytesLeft = " << bytesLeft << "\n";

        for (size_t i = 0; i < numSpecialDoors; ++i)
        {
            //std::cout << (currentByte - unknownDataBegin) << "\n";

            std::vector<Coord2d> specialOutlineCoords;
            std::vector<Coord3d> specialEntryCoords;

            std::cout
                << *reinterpret_cast<const uint16_t*>(currentByte) << ", " << *reinterpret_cast<const uint16_t*>(currentByte + 2) << ", " << *reinterpret_cast<const uint16_t*>(currentByte + 4) << "\n";

            uint16_t firstWord = *reinterpret_cast<const uint16_t*>(currentByte);
            currentByte += sizeof(uint16_t);

            switch (firstWord)
            {
            case 256:
                {
                    currentByte += 5 * sizeof(uint16_t);

                    break;
                }
    
            case 259:
                {
                    currentByte += 4 * sizeof(uint16_t);

                    auto numOutlineCoords = *reinterpret_cast<const uint16_t*>(currentByte);
                    currentByte += sizeof(uint16_t);

                    for (size_t j = 0; j < numOutlineCoords; ++j)
                    {
                        specialOutlineCoords.push_back(*reinterpret_cast<const Coord2d*>(currentByte));
                        currentByte += sizeof(Coord2d);
                    }
    
                    break;
                }
            default:
                currentByte += 6 * sizeof(uint16_t);
                break;
            }

            auto numSpecialPosCoords = *reinterpret_cast<const uint16_t*>(currentByte);
            currentByte += sizeof(uint16_t);

            for (size_t j = 0; j < numSpecialPosCoords; ++j)
            {
                specialEntryCoords.push_back(*reinterpret_cast<const Coord3d*>(currentByte));
                currentByte += sizeof(Coord3d);
            }

            currentByte += 1 * sizeof(uint16_t);

            specialDoors.push_back(std::make_shared<Door>(
                specialOutlineCoords,
                specialEntryCoords,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0
            ));
        }

        //assert(currentByte == endOfData);
        */
        while (currentByte < endOfData)
        {
            std::cout /* << std::hex << std::setfill('0') << std::setw(2) */ << *reinterpret_cast<const uint16_t*>(currentByte) << "\n";
            currentByte += sizeof(uint16_t);
        }
    }


    //std::vector<std::pair<std::vector<Coord2d>, std::vector<Coord3d>>> specialDoorCoords;

    struct DoorHelper
    {
        std::vector<Coord2d> outlineCoords;
        std::vector<Coord3d> entryCoords;

        uint8_t type          = 1;
        uint8_t locked        = 0;
        uint8_t unknownByte01 = 0;
        uint8_t lockPickable  = 0;
        uint8_t unknownByte04 = 0;
        uint8_t unknownByte05 = 0;
        uint8_t unknownByte06 = 0;
        uint8_t unknownByte07 = 0;
        uint8_t unknownByte08 = 0;
        uint8_t unknownByte09 = 0;
    };

    std::vector<DoorHelper> specialDoorHelpers;

    /*
    specialDoorHelpers = {
        DoorHelper{
            .outlineCoords = {},
            .entryCoords = {},
        },
    };
    */

    // Hardcode these until we know how to extract them programmatically.

    if (levelName == "level_03")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{862, 445}, {851, 461}, {841, 477}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1612, 664}, {1641, 665}, {1668, 666}},
            },
        };
    }
    else if (levelName == "level_05")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {{281, 388}, {281, 344}, {303, 336}, {303, 380}},
                .entryCoords = {{303, 398}, {292, 386}, {277, 376}},
            },
        };
    }
    else if (levelName == "level_06")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {{1323, 294}, {1323, 257}, {1328, 250}, {1334, 247}, {1338, 251}, {1338, 287}},
                .entryCoords = {{1321, 282}, {1331, 290}, {1340, 298}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1565, 974}, {1565, 984}, {1565, 995}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1685, 1031}, {1674, 1019}, {1666, 1011}},
            },
        };
    }
    else if (levelName == "level_08") {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {{1374, 942}, {1346, 917}, {1355, 860}, {1365, 862}, {1372, 873}, {1374, 890}},
                .entryCoords = {{1339, 933}, {1356, 925}, {1375, 917}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{242, 298}, {225, 290}, {209, 278}},
            },
        };
    }
    else if (levelName == "level_09")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{850, 348}, {881, 330}, {896, 304}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{874, 360}, {888, 334}, {922, 317}},
            },
        };
    }
    else if (levelName == "level_10")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{572, 1197}, {580, 1185}, {583, 1172}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{601, 1196}, {600, 1185}, {598, 1170}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{624, 1187}, {616, 1175}, {612, 1163}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{641, 1174}, {632, 1165}, {624, 1155}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{655, 1164}, {645, 1158}, {636, 1147}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{518, 1077}, {508, 1070}, {494, 1064}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{535, 1069}, {520, 1063}, {508, 1059}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1105, 666}, {1111, 648}, {1122, 636}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{383, 1651}, {398, 1651}, {413, 1657}},
            },
            DoorHelper{
                .outlineCoords = {{688, 1836}, {688, 1800}, {690, 1790}, {701, 1782}, {711, 1782}, {723, 1785}, {735, 1791}, {744, 1800}, {752, 1811}, {754, 1825}, {753, 1853}},
                .entryCoords = {{697, 1872}, {719, 1844}, {755, 1787}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{662, 1873}, {704, 1838}, {725, 1780}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{713, 1894}, {734, 1847}, {777, 1793}},
            },
            DoorHelper{
                .outlineCoords = {{841, 392}, {841, 362}, {844, 354}, {850, 351}, {854, 355}, {854, 382}},
                .entryCoords = {{860, 401}, {849, 391}, {839, 378}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{824, 1079}, {835, 1065}, {843, 1050}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{804, 1071}, {823, 1062}, {836, 1048}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{835, 1085}, {847, 1069}, {849, 1052}},
            },
        };
    }
    else if (levelName == "level_11")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{515, 355}, {515, 326}, {515, 297}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{338, 101}, {279, 115}, {262, 149}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{723, 387}, {729, 377}, {735, 367}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1074, 1761}, {1060, 1752}, {1043, 1742}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{211, 1834}, {211, 1822}, {212, 1807}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{233, 1069}, {248, 1064}, {265, 1059}},
            },
        };
    }
    else if (levelName == "level_12")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{242, 549}, {244, 538}, {245, 529}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{691, 915}, {673, 900}, {650, 901}},
            },
        };
    }
    else if (levelName == "level_13")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {{489, 360}, {477, 373}, {477, 341}, {489, 329}},
                .entryCoords = {{498, 374}, {485, 369}, {469, 362}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{826, 1310}, {876, 1282}, {873, 1260}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{958, 1325}, {934, 1284}, {937, 1266}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{895, 1297}, {896, 1283}, {898, 1268}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{917, 1297}, {916, 1283}, {917, 1283}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{759, 753}, {745, 745}, {729, 736}},
            },
            DoorHelper{
                .outlineCoords = {{764, 726}, {724, 767}, {724, 720}, {738, 692}, {764, 687}},
                .entryCoords = {{766, 747}, {751, 750}, {736, 732}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{739, 768}, {731, 757}, {720, 751}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{746, 758}, {738, 750}, {729, 744}},
            },
        };
    }
    else if (levelName == "level_14")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{738, 1006}, {732, 1012}, {726, 1019}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{720, 1001}, {713, 1001}, {705, 1014}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{757, 1010}, {755, 1017}, {749, 1023}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{728, 1004}, {723, 1011}, {717, 1017}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{754, 1005}, {747, 1013}, {739, 1021}},
            },
        };
    }
    else if (levelName == "level_15")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {{1796, 971}, {1788, 963}, {1788, 944}, {1796, 952}, {1796, 971}},
                .entryCoords = {{1782, 971}, {1782, 971}, {1782, 971}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{698, 776}, {712, 765}, {732, 758}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{902, 716}, {881, 711}, {859, 717}},
            },
            DoorHelper{
                .outlineCoords = {{1490, 999}, {1491, 962}, {1495, 958}, {1504, 954}, {1508, 993}},
                .entryCoords = {{1512, 1007}, {1500, 995}, {1490, 983}},
            },
            DoorHelper{
                .outlineCoords = {{1652, 963}, {1642, 954}, {1642, 917}, {1652, 927}},
                .entryCoords = {{1629, 965}, {1649, 960}, {1665, 951}},
            },
            DoorHelper{
                .outlineCoords = {{702, 320}, {659, 334}, {659, 304}, {666, 289}, {678, 281}, {688, 279}, {698, 282}, {702, 290}},
                .entryCoords = {{687, 327}, {682, 327}, {677, 319}},
            },
            DoorHelper{
                .outlineCoords = {{1799, 523}, {1799, 487}, {1811, 473}, {1828, 468}, {1839, 473}, {1840, 510}},
                .entryCoords = {{1835, 529}, {1822, 516}, {1809, 501}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1840, 524}, {1829, 513}, {1806, 502}},
            },
        };
    }
    else if (levelName == "level_17")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{99, 641}, {106, 619}, {120, 606}},
            },
        };
    }
    else if (levelName == "level_19")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{522, 334}, {535, 315}, {551, 309}},
            },
        };
    }
    else if (levelName == "level_21")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1309, 109}, {1346, 105}, {1384, 99}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1326, 117}, {1346, 115}, {1371, 109}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1317, 93}, {1344, 94}, {1372, 93}},
            },
        };
    }
    else if (levelName == "level_22")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1481, 1641}, {1455, 1646}, {1426, 1655}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{655, 1286}, {638, 1298}, {620, 1311}},
            },
        };
    }
    else if (levelName == "level_23")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1288, 549}, {1296, 537}, {1310, 530}},
            },
        };
    }
    else if (levelName == "level_24")
    {
        specialDoorHelpers = {
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{396, 862}, {396, 854}, {394, 846}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{835, 476}, {836, 467}, {837, 459}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1326, 799}, {1335, 805}, {1344, 811}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1007, 193}, {1017, 185}, {1028, 177}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1195, 355}, {1196, 363}, {1197, 370}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{1785, 1545}, {1800, 1534}, {1813, 1524}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{2576, 1277}, {2567, 1248}, {2561, 1229}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{2446, 1066}, {2432, 1061}, {2415, 1055}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{2393, 804}, {2402, 796}, {2407, 787}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{2247, 1357}, {2241, 1328}, {2233, 1295}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{2584, 521}, {2574, 514}, {2569, 505}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{2550, 312}, {2543, 306}, {2526, 302}},
            },
            DoorHelper{
                .outlineCoords = {{504, 404}, {454, 385}, {454, 349}, {462, 344}, {495, 357}, {504, 369}},
                .entryCoords = {{472, 408}, {477, 397}, {485, 386}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{307, 1343}, {317, 1338}, {328, 1330}},
            },
            DoorHelper{
                .outlineCoords = {},
                .entryCoords = {{297, 1333}, {305, 1329}, {315, 1316}},
            },
        };
    }

    for (const auto& helper : specialDoorHelpers)
    {
        specialDoors.push_back(std::make_shared<Door>(
            helper.outlineCoords,
            helper.entryCoords,
            helper.type,
            helper.locked,
            helper.unknownByte01,
            helper.lockPickable,
            helper.unknownByte04,
            helper.unknownByte05,
            helper.unknownByte06,
            helper.unknownByte07,
            helper.unknownByte08,
            helper.unknownByte09
       ));
    }

    return {buildings, specialDoors};
}
