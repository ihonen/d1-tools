extern "C" {
#include "lib/level/map.h"
#include "lib/level/level.h"
#include "lib/image/pixel.h"
}

#include "app/level-editor/mapview.hh"
#include "lib/common/log.hh"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>

#include <iostream>

// -----------------------------------------------------------------------------

using d1::level_editor::MapView;

// -----------------------------------------------------------------------------

MapView::MapView(
    QWidget* parent
)
    : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);

    setStyleSheet("QGraphicsView { background: #000000; }");
}

void MapView::setLevel(
    D1Level* level
)
{
    m_level = level;
    auto map = D1Level_map(level);

    auto width = D1Map_width(map);
    auto height = D1Map_height(map);

    QImage image(
        reinterpret_cast<const uchar*>(D1Map_pixels(map)),
        width,
        height,
        QImage::Format_BGR888
    );

    m_scene->clear();
    m_scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(image)));
    m_scene->setSceneRect(0, 0, width, height);
}
