#pragma once

#include "app/graphicsitem.hh"
#include "world/worlditem.hh"

#include <QObject>

// -----------------------------------------------------------------------------

class ObjectMap
    : public QObject
{
    Q_OBJECT
public:
    
    static ObjectMap& get();

    std::shared_ptr<GraphicsItem>& getGraphicsItem(const std::shared_ptr<WorldItem>& worldItem);
    std::shared_ptr<WorldItem>& getWorldItem(const std::shared_ptr<GraphicsItem>& graphicsItem);

    void mapGraphicsItemToWorldItem(
        const std::shared_ptr<graphicsItem>& graphicsItem,
        const std::shared_ptr<worldItem>& worldItem
    );

private:
};
