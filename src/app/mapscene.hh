#pragma once

#include <QGraphicsScene>

// -----------------------------------------------------------------------------

class QGraphicsSceneMouseEvent;
class QGraphicsView;

// -----------------------------------------------------------------------------

class MapScene
    : public QGraphicsScene
{
    Q_OBJECT

public:

    using QGraphicsScene::QGraphicsScene;
};
