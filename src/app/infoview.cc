#include "app/infoview.hh"
#include "world/building.hh"
#include "world/door.hh"
#include "world/material.hh"

#include <QGraphicsItem>

#include <bitset>
#include <iomanip>
#include <sstream>

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

        std::ostringstream text;
        
        text
            << "DOOR\n"
            << "type:     " << door->typeToString() << "\n"
            << "locked:   " << int(door->locked()) << "\n"
            << "pickable: " << int(door->lockPickable()) << "\n";
        
        for (const auto& coord : door->entryCoords())
        {
            text
                << "xyz:     "
                << std::setw(5) << std::right << coord.x
                << std::setw(5) << std::right << coord.y
                << std::setw(5) << std::right << coord.z
                << std::setw(5) << std::right << coord.zLayer
                << "\n";
        }

        text
            << "U8_01:    " << int(door->unknownByte01()) << "\n"
            << "U8_04:    " << int(door->unknownByte04()) << "\n"
            << "U8_05:    " << int(door->unknownByte05()) << "\n"
            << "U8_06:    " << int(door->unknownByte06()) << "\n"
            << "U8_07:    " << int(door->unknownByte07()) << "\n"
            << "U8_08:    " << int(door->unknownByte08()) << "\n"
            << "U8_09:    " << int(door->unknownByte09()) << "\n"
            << "U16_00:   " << int(door->unknownWord00()) << "\n"
            << "U8_10:    " << int(door->unknownByte10()) << "\n"
            << "U8_11:    " << int(door->unknownByte11()) << "\n";


        if (auto building = door->parent())
        {
            text << "\n";
            
            text
                << "BUILDING\n"
                << "U8_00:     " << std::bitset<8>(building->unknownByte00()) << " (" << int(building->unknownByte00()) << ")\n"
                << "U8_01:     " << int(building->unknownByte01()) << "\n"
                << "characters:\n";
            for (auto id : building->characterIds())
            {
                text << "  " << id << "\n";
            }
        }

        append(QString::fromStdString(text.str()));
    }
    else if (auto material = dynamic_cast<Material*>(worldItem.get()))
    {
        std::ostringstream text;

        text
            << "MATERIAL\n"
            << "unknownByte00: " << int(material->unknownByte00()) << "\n";

        append(QString::fromStdString(text.str()));
    }
}
