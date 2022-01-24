#include "app//mapview.hh"
#include "common/log.hh"
#include "image/pixel.hh"
#include "level/level.hh"
#include "level/map.hh"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>

#include <iostream>

// -----------------------------------------------------------------------------

MapView::MapView(QWidget* parent)
    : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);

    setStyleSheet("QGraphicsView { background: #000000; }");
}

void MapView::setLevel(const std::shared_ptr<Level>& level)
{
    m_level = level;
    const auto map = level->map();

    QImage image(
        reinterpret_cast<const uchar*>(map->pixels()),
        map->width(),
        map->height(),
        QImage::Format_BGR888
    );

    m_scene->clear();
    m_scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(image)));
    m_scene->setSceneRect(0, 0, map->width(), map->height());
}
