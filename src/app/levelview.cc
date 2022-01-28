#include "app/graphicsitem.hh"
#include "app/levelview.hh"
#include "app/levelscene.hh"
#include "common/log.hh"
#include "image/pixel.hh"
#include "world/level.hh"
#include "world/map.hh"

#include <QGraphicsPixmapItem>
#include <QImage>
#include <QMouseEvent>
#include <QPixmap>
#include <QTransform>

#include <iostream>

// -----------------------------------------------------------------------------

LevelView::LevelView(QWidget* parent)
    : QGraphicsView(parent)
{
    m_levelScene = new LevelScene(this);
    setScene(m_levelScene);

    setStyleSheet("QGraphicsView { background: #000000; }");

    setMouseTracking(true);
}

void LevelView::setLevel(const std::shared_ptr<Level>& level)
{
    m_level = level;
    
    m_levelScene->clear();
    m_worldItems.clear();
    m_graphicsItems.clear();

    m_mapLayer.clear();
    m_buildingsLayer.clear();
    m_materialsLayer.clear();

    drawMap();
    drawBuildings();
    drawMaterials();

    m_levelScene->setSceneRect(
        0,
        0,
        dynamic_cast<QGraphicsPixmapItem*>(m_mapItem)->pixmap().width(),
        dynamic_cast<QGraphicsPixmapItem*>(m_mapItem)->pixmap().height()
    );
}

void LevelView::drawMap()
{
    const auto& map = m_level->map();

    QImage image(
        reinterpret_cast<const uchar*>(map->pixels()),
        map->width(),
        map->height(),
        QImage::Format_BGR888
    );

    m_mapItem = m_levelScene->addPixmap(QPixmap::fromImage(image));
    m_mapLayer.push_back(m_mapItem);
}

void LevelView::drawBuildings()
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
}

void LevelView::drawDoor(const std::shared_ptr<Door>& door, const QPen& pen1, const QPen& pen2, const QBrush& brush1, const QBrush& brush2)
{
    const auto& outlineCoords = door->outlineCoords();
    for (size_t i = 0; i < outlineCoords.size(); ++i)
    {
        const auto& [x1, y1] = door->outlineCoords().at(i);
        const auto& [x2, y2] = door->outlineCoords().at(i < (outlineCoords.size() - 1) ? i + 1 : 0);

        auto item = m_levelScene->addLine(x1, y1, x2, y2, pen1);
        addItem(item, door, m_buildingsLayer);
    }

    const auto& entryCoords = door->entryCoords();
    if (entryCoords.size() >= 2)
    {
        for (size_t i = 0; i < entryCoords.size() - 1; ++i)
        {
            const auto& [x1, y1, z1, z_layer1] = door->entryCoords().at(i);
            const auto& [x2, y2, z2, z_layer2] = door->entryCoords().at(i + 1);

            auto item = m_levelScene->addLine(x1, y1, x2, y2, pen1);
            addItem(item, door, m_buildingsLayer);
        }
    }

    for (const auto& coord : outlineCoords)
    {
        auto item4 = m_levelScene->addRect(coord.x - 1, coord.y - 1, 3, 3, pen2, brush2);
        addItem(item4, door, m_buildingsLayer);
    }

    for (const auto& coord : entryCoords)
    {
        auto item4 = m_levelScene->addRect(coord.x - 1, coord.y - 1, 3, 3, pen2, brush2);
        addItem(item4, door, m_buildingsLayer);
    }
}

void LevelView::drawMaterials()
{
    static const QPen BrushPen = QPen(QColor{ 1, 193, 113 }, 3);
    static const QPen GrassPen = QPen(QColor{ 0, 175, 225 }, 3);
    static const QPen LightPen = QPen(QColor{ 255, 255, 0 }, 3);
    static const QPen WaterPen = QPen(QColor{ 168, 199, 31 }, 3);
    static const QPen WoodPen = QPen(QColor{ 241, 55, 100 }, 3);

    static const QPen DefaultPen = QPen(QColor{255, 0, 0}, 3);
    
    for (const auto& material : m_level->materials())
    {
        switch (material->unknownByte00())
        {
        case 0x01:
            drawMaterial(material, WoodPen);
            break;
        case 0x03:
            drawMaterial(material, GrassPen);
            break;
        case 0x05:
            drawMaterial(material, WaterPen);
            break;
        case 0x06:
            drawMaterial(material, BrushPen);
            break;
        case 0x08:
            drawMaterial(material, LightPen);
            break;
        default:
            drawMaterial(material, DefaultPen);
        }
    }
}

void LevelView::drawMaterial(const std::shared_ptr<Material>& material, const QPen& pen)
{
    const auto& area = material->area();
    for (size_t i = 0; i < area.size(); ++i)
    {
        const auto& [x1, y1] = area.at(i);
        const auto& [x2, y2] = area.at(i < (area.size() - 1) ? i + 1 : 0);

        auto item = m_levelScene->addLine(x1, y1, x2, y2, pen);
        addItem(item, material, m_materialsLayer);
    }
}

void LevelView::setMapVisible(bool visible)
{
    for (const auto& item : m_mapLayer)
    {
        item->setVisible(visible);
    }
}

bool LevelView::isMapVisible() const
{
    return m_mapLayer.empty() || m_mapLayer.at(0)->isVisible();
}

void LevelView::setBuildingsVisible(bool visible)
{
    for (const auto& item : m_buildingsLayer)
    {
        item->setVisible(visible);
    }
}

bool LevelView::isBuildingsVisible() const
{
    return m_buildingsLayer.empty() || m_buildingsLayer.at(0)->isVisible();
}

void LevelView::setMaterialsVisible(bool visible)
{
    for (const auto& item : m_materialsLayer)
    {
        item->setVisible(visible);
    }
}

bool LevelView::isMaterialsVisible() const
{
    return m_materialsLayer.empty() || m_materialsLayer.at(0)->isVisible();
}

void LevelView::addItem(
    QGraphicsItem* graphicsItem,
    const std::shared_ptr<WorldItem>& worldItem,
    std::vector<QGraphicsItem*>& layer
)
{
    layer.push_back(graphicsItem);
    m_worldItems[graphicsItem] = worldItem;
}

void LevelView::mouseMoveEvent(QMouseEvent* event)
{
    auto pos = mapToScene(event->pos());
    emit mousePositionChanged(pos.x(), pos.y());

    auto graphicsItem = m_levelScene->itemAt(mapToScene(event->pos()), QTransform());
    auto worldItem = m_worldItems.find(graphicsItem);
    if (worldItem != m_worldItems.end())
    {
        emit worldItemHovered(worldItem->second);
    }
}
