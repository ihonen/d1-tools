#pragma once

#include "level/worlditem.hh"

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>

#include <cassert>
#include <memory>

// -----------------------------------------------------------------------------

class GraphicsItem
{
public:

    virtual ~GraphicsItem() = default;

    void setWorldItem(const std::shared_ptr<WorldItem>& worldItem)
    {
        assert(!m_worldItem);
        m_worldItem = worldItem;
    }

    const std::shared_ptr<WorldItem>& getWorldItem()
    {
        assert(m_worldItem);
        return m_worldItem;
    }

private:
    std::shared_ptr<WorldItem> m_worldItem = nullptr;
};

// -----------------------------------------------------------------------------

class GraphicsEllipseItem
    : public QGraphicsEllipseItem
    , public GraphicsItem
{
};

// -----------------------------------------------------------------------------

class GraphicsLineItem
    : public QGraphicsLineItem
    , public GraphicsItem
{
};

// -----------------------------------------------------------------------------

class GraphicsPixmapItem
    : public QGraphicsPixmapItem
    , public GraphicsItem
{
};

// -----------------------------------------------------------------------------

class GraphicsPolygonItem
    : public QGraphicsPolygonItem
    , public GraphicsItem
{
};

// -----------------------------------------------------------------------------

class GraphicsRectItem
    : public QGraphicsRectItem
    , public GraphicsItem
{
};
