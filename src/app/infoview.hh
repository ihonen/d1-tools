#pragma once

#include <QGraphicsItem>
#include <QTextBrowser>

class WorldItem;

// -----------------------------------------------------------------------------

class InfoView
    : public QTextBrowser
{
    Q_OBJECT
public:

    InfoView(QWidget* parent = nullptr);

    void displayWorldItem(const std::shared_ptr<WorldItem>& worldItem);
};
