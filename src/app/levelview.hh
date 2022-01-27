#pragma once

#include <QGraphicsView>

#include <map>

// -----------------------------------------------------------------------------

class Door;
class GraphicsItem;
class Level;
class LevelScene;
class WorldItem;

// -----------------------------------------------------------------------------

class LevelView
    : public QGraphicsView
{
    Q_OBJECT
public:

    LevelView(QWidget* parent = nullptr);

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
    void drawDoor(const std::shared_ptr<Door>& door, const QPen& pen1, const QPen& pen2, const QBrush& brush1, const QBrush& brush2);

    void mouseMoveEvent(QMouseEvent* event) override;
    
    LevelScene* m_levelScene = nullptr;
    QGraphicsItem* m_mapItem = nullptr;

    std::vector<QGraphicsItem*> m_mapLayer;
    std::vector<QGraphicsItem*> m_buildingsLayer;

    std::map<QGraphicsItem*, std::shared_ptr<WorldItem>> m_worldItems;
    std::map<std::shared_ptr<WorldItem>, QGraphicsItem*> m_graphicsItems;

    std::shared_ptr<Level> m_level = nullptr;
};
