#pragma once

#include <QGraphicsView>

// -----------------------------------------------------------------------------

class Level;
class MapScene;

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

private:

    void clearMap();
    void drawMap();

    void clearBuildings();
    void drawBuildings();

    void mouseMoveEvent(QMouseEvent* event) override;

    MapScene* m_scene = nullptr;
    std::shared_ptr<Level> m_level = nullptr;
    QGraphicsItem* m_mapItem = nullptr;
    std::vector<QGraphicsItem*> m_builLayerItems;
};
