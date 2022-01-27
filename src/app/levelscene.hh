#pragma once

#include <QGraphicsScene>

// -----------------------------------------------------------------------------

class QGraphicsSceneMouseEvent;
class QGraphicsView;

// -----------------------------------------------------------------------------

class LevelScene
    : public QGraphicsScene
{
    Q_OBJECT

public:

    using QGraphicsScene::QGraphicsScene;
};
