#pragma once

#include <QGraphicsItem>
#include <QTextBrowser>

class Door;
class MaterialZone;
class WorldItem;

// -----------------------------------------------------------------------------

class InfoView
    : public QTextBrowser
{
    Q_OBJECT
public:

    InfoView(QWidget* parent = nullptr);

    void displayWorldItem(const std::shared_ptr<WorldItem>& worldItem);

private:

    void displayDoor(const Door* door);
    void displayMaterial(const MaterialZone* materialZone);
};
