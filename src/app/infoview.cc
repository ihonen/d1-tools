#include "app/infoview.hh"
#include "world/building.hh"
#include "world/door.hh"
#include "world/material.hh"

#include <QGraphicsItem>

#include <bitset>
#include <iomanip>
#include <sstream>

// -----------------------------------------------------------------------------

namespace
{

    template<typename T>
    std::string hex(const T& value)
    {
        std::ostringstream text;
        text << std::setfill('0') << std::hex;
        text << "0x" << std::setw(sizeof(T) * 2) << static_cast<uint64_t>(value);
        return text.str();
    }

    template<typename T>
    std::string hex(const std::optional<T>& value)
    {
        if (value)
        {
            return hex<T>(*value);
        }

        return "N/A";
    }

}

// -----------------------------------------------------------------------------

InfoView::InfoView(QWidget* parent)
    : QTextBrowser(parent)
{
    auto myFont = font();
    myFont.setFamily("Courier");
    myFont.setBold(true);
    myFont.setPointSize(15);
    setFont(myFont);
}

void InfoView::displayWorldItem(const std::shared_ptr<WorldItem>& worldItem)
{
    clear();

    if (auto door = dynamic_cast<Door*>(worldItem.get()))
    {
        displayDoor(door);

    }
    else if (auto materialZone = dynamic_cast<MaterialZone*>(worldItem.get()))
    {
        displayMaterial(materialZone);
    }
}

void InfoView::displayDoor(const Door* door)
{
    std::ostringstream text;

    const auto& outCoord = door->entryCoords().at(0);
    const auto& onCoord = door->entryCoords().at(1);
    const auto& inCoord = door->entryCoords().at(2);

    text << "DOOR\n";
    
    text << "Out:        " << outCoord.x << " " << outCoord.y << " " << outCoord.z << " (" << outCoord.zLayer << ")\n";
    text << "On:         " << onCoord.x << " " << onCoord.y << " " << onCoord.z << " (" << onCoord.zLayer << ")\n";
    text << "In:         " << inCoord.x << " " << inCoord.y << " " << inCoord.z << " (" << inCoord.zLayer << ")\n";
    text << "Type:       " << door->typeToString() << "\n";
    text << "Locked:     " << hex<uint8_t>(door->locked()) << "\n";
    text << "Unlockable: " << hex<uint8_t>(door->lockPickable()) << "\n";

    text << "Unk8_01:    " << hex<uint8_t>(door->unknownByte01()) << "\n";
    text << "Unk8_04:    " << hex<uint8_t>(door->unknownByte04()) << "\n";
    text << "Unk8_05:    " << hex<uint8_t>(door->unknownByte05()) << "\n";
    text << "Unk8_06:    " << hex<uint8_t>(door->unknownByte06()) << "\n";
    text << "Unk8_07:    " << hex<uint8_t>(door->unknownByte07()) << "\n";
    text << "Unk8_08:    " << hex<uint8_t>(door->unknownByte08()) << "\n";
    text << "Unk8_09:    " << hex<uint8_t>(door->unknownByte09()) << "\n";
    text << "Unk16_00:   " << hex<uint16_t>(door->unknownWord00()) << "\n";
    text << "Unk8_10:    " << hex<uint8_t>(door->unknownByte10()) << "\n";
    text << "Unk8_11:    " << hex<uint8_t>(door->unknownByte11()) << "\n";

    if (auto building = door->parent())
    {
        text << "\n";

        text << "BUILDING\n";
        text << "NPCs:     ";
        for (auto id : building->characterIds())
        {
            text << id << " ";
        }
        text << "\n";
        text << "Unk8_00:  " << hex<uint8_t>(building->unknownByte00()) << "\n";
        text << "Unk8_01:  " << hex<uint8_t>(building->unknownByte01()) << "\n";
    }

    clear();
    append(QString::fromStdString(text.str()));
}

void InfoView::displayMaterial(const MaterialZone* materialZone)
{
    std::ostringstream text;

    text
        << "MATERIAL\n"
        << "Type:     " << materialZone->typeToString() << "\n"
        << "Section:  " << materialZone->sectionNumber() << "\n"
        << "Unk16_00: " << hex<uint16_t>(materialZone->unknownWord00()) << "\n";

    text << "Unk8_00:  " << hex<uint8_t>(materialZone->unknownByte00()) << "\n";
    text << "Unk8_01:  " << hex<uint8_t>(materialZone->unknownByte01()) << "\n";
    text << "Unk8_02:  " << hex<uint8_t>(materialZone->unknownByte02()) << "\n";
    text << "Unk8_03:  " << hex<uint8_t>(materialZone->unknownByte03()) << "\n";
    text << "Unk8_04:  " << hex<uint8_t>(materialZone->unknownByte04()) << "\n";
    text << "Unk8_05:  " << hex<uint8_t>(materialZone->unknownByte05()) << "\n";
    text << "Unk8_06:  " << hex<uint8_t>(materialZone->unknownByte06()) << "\n";

    text << "Unk32_00: " << hex<uint32_t>(materialZone->unknownDword00()) << "\n";

    /*
    if (auto value = materialZone->unknownByte00())
    {
        text << std::setw(2) << int(*value) << "\n";
    }
    else
    {
        text << "N/A\n";
    }

    text << "Unk8_01:  ";
    if (auto value = materialZone->unknownByte01())
    {
        text << std::setw(2) << int(*value) << "\n";
    }
    else
    {
        text << "N/A\n";
    }

    text << "Unk8_02:  ";
    if (auto value = materialZone->unknownByte02())
    {
        text << std::setw(2) << int(*value) << "\n";
    }
    else
    {
        text << "N/A\n";
    }

    text << "Unk8_03:  ";
    if (auto value = materialZone->unknownByte03())
    {
        text << std::setw(2) << int(*value) << "\n";
    }
    else
    {
        text << "N/A\n";
    }

    text << "Unk8_04:  ";
    if (auto value = materialZone->unknownByte04())
    {
        text << std::setw(2) << int(*value) << "\n";
    }
    else
    {
        text << "N/A\n";
    }

    text << "Unk8_05:  ";
    if (auto value = materialZone->unknownByte05())
    {
        text << std::setw(2) << int(*value) << "\n";
    }
    else
    {
        text << "N/A\n";
    }

    text << "Unk8_06:  ";
    if (auto value = materialZone->unknownByte06())
    {
        text << std::setw(2) << int(*value) << "\n";
    }
    else
    {
        text << "N/A\n";
    }

    text << "Unk32_00: ";
    if (auto value = materialZone->unknownDword00())
    {
        text << std::setw(2) << int(*value) << "\n";
    }
    else
    {
        text << "N/A\n";
    }
    */

    append(QString::fromStdString(text.str()));
}
