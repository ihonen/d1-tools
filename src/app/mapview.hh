#pragma once

#include <QGraphicsView>

// -----------------------------------------------------------------------------

class Level;

class QGraphicsScene;

// -----------------------------------------------------------------------------

class MapView
    : public QGraphicsView
{
    Q_OBJECT
public:

    MapView(QWidget* parent = nullptr);

    void setLevel(const std::shared_ptr<Level>& level);

private:

    QGraphicsScene* m_scene = nullptr;
    std::shared_ptr<Level> m_level = nullptr;
};
