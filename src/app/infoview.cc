#include "app/infoview.hh"
#include "level/building.hh"
#include "level/door.hh"

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
        
        if (auto building = door->parent())
        {
            text
                << "BUILDING\n"
                << "U16_00: " << std::bitset<16>(building->unknownWord00()) << " " << building->unknownWord00() << "\n"
                << "characterIds:";
            for (auto id : building->characterIds())
            {
                text << " " << id;
            }
            text << "\n";
        
            text << "\n";
        }
        
        text
            << "DOOR\n"
            << "type:      " << int(door->type()) << "\n"
            << "locked:    " << int(door->locked()) << "\n"
            << "pickable:  " << int(door->lockPickable()) << "\n"
            << "U8_04:     " << int(door->unknownByte04()) << "\n"
            << "U8_05:     " << int(door->unknownByte05()) << "\n";

        for (const auto& coord : door->entryCoords())
        {
            text
                << "xyz:"
                << std::setw(5) << std::right << coord.x
                << std::setw(5) << std::right << coord.y
                << std::setw(5) << std::right << coord.z
                << std::setw(5) << std::right << coord.zLayer
                << "\n";
        }
        append(QString::fromStdString(text.str()));
    }
}
