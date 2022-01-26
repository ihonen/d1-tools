#pragma once

#include <QGraphicsView>

#include <map>

// -----------------------------------------------------------------------------

class GraphicsItem;
class Level;
class MapScene;
class WorldItem;

// -----------------------------------------------------------------------------

class MapView
    : public QGraphicsView
{
    Q_OBJECT
public:

    MapView(QWidget* parent = nullptr);

    void setLevel(const std::shared_ptr<Level>& level);

    void setMapVisible(bool visible);
    bool isMapVisible() const;

    void setBuildingsVisible(bool visible);
    bool isBuildingsVisible() const;

signals:

    void mousePositionChanged(int x, int y);
    void worldItemHovered(const std::shared_ptr<WorldItem>& worldItem);

private:

    void addItem(
        QGraphicsItem* graphicsItem,
        const std::shared_ptr<WorldItem>& worldItem,
        std::vector<QGraphicsItem*>& layer
    );

    void drawMap();
    void drawBuildings();

    void mouseMoveEvent(QMouseEvent* event) override;
    
    MapScene* m_scene = nullptr;
    QGraphicsItem* m_mapItem = nullptr;

    std::vector<QGraphicsItem*> m_mapLayer;
    std::vector<QGraphicsItem*> m_buildingsLayer;

    std::map<QGraphicsItem*, std::shared_ptr<WorldItem>> m_worldItems;
    std::map<std::shared_ptr<WorldItem>, QGraphicsItem*> m_graphicsItems;

    std::shared_ptr<Level> m_level = nullptr;
};
