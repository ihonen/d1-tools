#include "app/graphicsitem.hh"
#include "app/mapview.hh"
#include "app/mapscene.hh"
#include "common/log.hh"
#include "image/pixel.hh"
#include "level/level.hh"
#include "level/map.hh"

#include <QGraphicsPixmapItem>
#include <QImage>
#include <QMouseEvent>
#include <QPixmap>
#include <QTransform>

#include <iostream>

// -----------------------------------------------------------------------------

MapView::MapView(QWidget* parent)
    : QGraphicsView(parent)
{
    m_scene = new MapScene(this);
    setScene(m_scene);

    setStyleSheet("QGraphicsView { background: #000000; }");

    setMouseTracking(true);
}

void MapView::setLevel(const std::shared_ptr<Level>& level)
{
    m_level = level;
    
    m_scene->clear();
    m_worldItems.clear();
    m_graphicsItems.clear();

    m_mapLayer.clear();
    m_buildingsLayer.clear();

    drawMap();
    drawBuildings();

    m_scene->setSceneRect(
        0,
        0,
        dynamic_cast<QGraphicsPixmapItem*>(m_mapItem)->pixmap().width(),
        dynamic_cast<QGraphicsPixmapItem*>(m_mapItem)->pixmap().height()
    );
}

void MapView::drawMap()
{
    const auto map = m_level->map();

    QImage image(
        reinterpret_cast<const uchar*>(map->pixels()),
        map->width(),
        map->height(),
        QImage::Format_BGR888
    );

    m_mapItem = m_scene->addPixmap(QPixmap::fromImage(image));
    m_mapLayer.push_back(m_mapItem);
}

void MapView::drawBuildings()
{
    static const auto Pen1 = QPen(QColor{0, 0, 255}, 3);
    static const auto Pen2 = QPen(QColor{255, 0, 255}, 1);
    static const auto Pen3 = QPen(QColor{0, 255, 0}, 3);

    static const auto Brush1 = QBrush(QColor{ 0, 0, 255 });
    static const auto Brush2 = QBrush(QColor{255, 0, 255});
    static const auto Brush3 = QBrush(QColor{0, 255, 0});

    for (const auto& building : m_level->buildings())
    {
        for (const auto& door : building->doors())
        {
            drawDoor(door, Pen1, Pen2, Brush1, Brush2);
        }
    }

    for (const auto& door : m_level->specialDoors())
    {
        drawDoor(door, Pen3, Pen2, Brush3, Brush2);
    }


    /*
    for (const auto& specialDoor : m_level->specialDoors())
    {
        const auto& outlineCoords = specialDoor->outlineCoords();
        for (size_t i = 0; i < outlineCoords.size(); ++i)
        {
            const auto& [x1, y1] = specialDoor->outlineCoords().at(i);
            const auto& [x2, y2] = specialDoor->outlineCoords().at(i < (outlineCoords.size() - 1) ? i + 1 : 0);

            auto item = m_scene->addLine(x1, y1, x2, y2, Pen3);
            addItem(item, specialDoor, m_buildingsLayer);
        }

        const auto& entryCoords = specialDoor->entryCoords();
        if (entryCoords.size() >= 2)
        {
            for (size_t i = 0; i < entryCoords.size() - 1; ++i)
            {
                const auto& [x1, y1, z1, z_layer1] = specialDoor->entryCoords().at(i);
                const auto& [x2, y2, z2, z_layer2] = specialDoor->entryCoords().at(i + 1);

                auto item = m_scene->addLine(x1, y1, x2, y2, Pen3);
                addItem(item, specialDoor, m_buildingsLayer);
            }
        }

        for (const auto& coord : outlineCoords)
        {
            auto item4 = m_scene->addRect(coord.x - 1, coord.y - 1, 3, 3, Pen2, Brush2);
            addItem(item4, specialDoor, m_buildingsLayer);
        }

        for (const auto& coord : entryCoords)
        {
            auto item4 = m_scene->addRect(coord.x - 1, coord.y - 1, 3, 3, Pen2, Brush2);
            addItem(item4, specialDoor, m_buildingsLayer);
        }
    }
    */
}

void MapView::drawDoor(const std::shared_ptr<Door>& door, const QPen& pen1, const QPen& pen2, const QBrush& brush1, const QBrush& brush2)
{
    const auto& outlineCoords = door->outlineCoords();
    for (size_t i = 0; i < outlineCoords.size(); ++i)
    {
        const auto& [x1, y1] = door->outlineCoords().at(i);
        const auto& [x2, y2] = door->outlineCoords().at(i < (outlineCoords.size() - 1) ? i + 1 : 0);

        auto item = m_scene->addLine(x1, y1, x2, y2, pen1);
        addItem(item, door, m_buildingsLayer);
    }

    const auto& entryCoords = door->entryCoords();
    if (entryCoords.size() >= 2)
    {
        for (size_t i = 0; i < entryCoords.size() - 1; ++i)
        {
            const auto& [x1, y1, z1, z_layer1] = door->entryCoords().at(i);
            const auto& [x2, y2, z2, z_layer2] = door->entryCoords().at(i + 1);

            auto item = m_scene->addLine(x1, y1, x2, y2, pen1);
            addItem(item, door, m_buildingsLayer);
        }
    }

    for (const auto& coord : outlineCoords)
    {
        auto item4 = m_scene->addRect(coord.x - 1, coord.y - 1, 3, 3, pen2, brush2);
        addItem(item4, door, m_buildingsLayer);
    }

    for (const auto& coord : entryCoords)
    {
        auto item4 = m_scene->addRect(coord.x - 1, coord.y - 1, 3, 3, pen2, brush2);
        addItem(item4, door, m_buildingsLayer);
    }
}

void MapView::setMapVisible(bool visible)
{
     m_mapItem->setVisible(visible);
}

bool MapView::isMapVisible() const
{
    return m_mapItem->isVisible();
}

void MapView::setBuildingsVisible(bool visible)
{
    for (const auto& item : m_buildingsLayer)
    {
        item->setVisible(visible);
    }
}

bool MapView::isBuildingsVisible() const
{
    return m_buildingsLayer.size() == 0 || m_buildingsLayer.at(0)->isVisible();
}

void MapView::addItem(
    QGraphicsItem* graphicsItem,
    const std::shared_ptr<WorldItem>& worldItem,
    std::vector<QGraphicsItem*>& layer
)
{
    layer.push_back(graphicsItem);
    m_worldItems[graphicsItem] = worldItem;
}

void MapView::mouseMoveEvent(QMouseEvent* event)
{
    auto pos = mapToScene(event->pos());
    emit mousePositionChanged(pos.x(), pos.y());

    auto graphicsItem = m_scene->itemAt(mapToScene(event->pos()), QTransform());
    auto worldItem = m_worldItems.find(graphicsItem);
    if (worldItem != m_worldItems.end())
    {
        emit worldItemHovered(worldItem->second);
    }
}
