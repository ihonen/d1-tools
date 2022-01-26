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
    static const auto Brush2 = QBrush(QColor{255, 0, 255});

    for (const auto& building : m_level->buildings())
    {
        for (const auto& door : building->doors())
        {
            const auto& outlineCoords = door->outlineCoords();
            for (size_t i = 0; i < outlineCoords.size(); ++i)
            {
                const auto& [x1, y1] = door->outlineCoords().at(i);
                const auto& [x2, y2] = door->outlineCoords().at(i < (outlineCoords.size() - 1) ? i + 1 : 0);

                auto item = m_scene->addLine(x1, y1, x2, y2, Pen1);
                addItem(item, door, m_buildingsLayer);
            }

            const auto& entryCoords = door->entryCoords();
            if (entryCoords.size() >= 2)
            {
                for (size_t i = 0; i < entryCoords.size() - 1; ++i)
                {
                    const auto& [x1, y1, z1, z_layer1] = door->entryCoords().at(i);
                    const auto& [x2, y2, z2, z_layer2] = door->entryCoords().at(i + 1);

                    auto item = m_scene->addLine(x1, y1, x2, y2, Pen1);
                    addItem(item, door, m_buildingsLayer);
                }
            }

            for (const auto& coord : outlineCoords)
            {
                auto item4 = m_scene->addRect(coord.x - 1, coord.y - 1, 3, 3, Pen2, Brush2);
                addItem(item4, door, m_buildingsLayer);
            }

            for (const auto& coord : entryCoords)
            {
                auto item4 = m_scene->addRect(coord.x - 1, coord.y - 1, 3, 3, Pen2, Brush2);
                addItem(item4, door, m_buildingsLayer);
            }
        }
    }

    /*
    std::vector<std::vector<Coord>> pointsOfInterest;

    if (m_level->name() == "level_03")
    {
        pointsOfInterest = {
            {{862, 445}, {851, 461}, {841, 477}},
            {{1612, 664}, {1641, 665}, {1668, 666}},
        };
    }
    else if (m_level->name() == "level_05")
    {
        pointsOfInterest = {
            {{281, 388}, {281, 344}, {303, 336}, {303, 380}},
            {{303, 398}, {292, 386}, {277, 376}},
       };
    }
    else if (m_level->name() == "level_06")
    {
        pointsOfInterest = {
            {{1323, 294}, {1323, 257}, {1328, 250}, {1334, 247}, {1338, 251}, {1338, 287}},
            {{1321, 282}, {1331, 290}, {1340, 298}},
            {{1565, 974}, {1565, 984}, {1565, 995}},
            {{1685, 1031}, {1674, 1019}, {1666, 1011}},
        };
    }
    else if (m_level->name() == "level_08") {
        pointsOfInterest = {
            {{1374, 942}, {1346, 917}, {1355, 860}, {1365, 862}, {1372, 873}, {1374, 890}},
            {{1339, 933}, {1356, 925}, {1375, 917}},
            {{242, 298}, {225, 290}, {209, 278}},
        };
    }
    else if (m_level->name() == "level_09")
    {
        pointsOfInterest = {
            {{850, 348}, {881, 330}, {896, 304}},
            {{874, 360}, {888, 334}, {922, 317}},
        };
    }
    else if (m_level->name() == "level_10")
    {
        pointsOfInterest = {
            {{572, 1197}, {580, 1185}, {583, 1172}},
            {{601, 1196}, {600, 1185}, {598, 1170}},
            {{624, 1187}, {616, 1175}, {612, 1163}},
            {{641, 1174}, {632, 1165}, {624, 1155}},
            {{655, 1164}, {645, 1158}, {636, 1147}},
            {{518, 1077}, {508, 1070}, {494, 1064}},
            {{535, 1069}, {520, 1063}, {508, 1059}},
            {{1105, 666}, {1111, 648}, {1122, 636}},
            {{383, 1651}, {398, 1651}, {413, 1657}},
            {{688, 1836}, {688, 1800}, {690, 1790}, {701, 1782}, {711, 1782}, {723, 1785}, {735, 1791}, {744, 1800}, {752, 1811}, {754, 1825}, {753, 1853}},
            {{697, 1872}, {719, 1844}, {755, 1787}},
            {{662, 1873}, {704, 1838}, {725, 1780}},
            {{713, 1894}, {734, 1847}, {777, 1793}},
            {{841, 392}, {841, 362}, {844, 354}, {850, 351}, {854, 355}, {854, 382}},
            {{860, 401}, {849, 391}, {839, 378}},
            {{824, 1079}, {835, 1065}, {843, 1050}},
            {{804, 1071}, {823, 1062}, {836, 1048}},
            {{835, 1085}, {847, 1069}, {849, 1052}},
        };
    }
    else if (m_level->name() == "level_11")
    {
        pointsOfInterest = {
            {{515, 355}, {515, 326}, {515, 297}},
            {{338, 101}, {279, 115}, {262, 149}},
            {{723, 387}, {729, 377}, {735, 367}},
            {{1074, 1761}, {1060, 1752}, {1043, 1742}},
            {{211, 1834}, {211, 1822}, {212, 1807}},
            {{233, 1069}, {248, 1064}, {265, 1059}},
        };
    }
    else if (m_level->name() == "level_12")
    {
        pointsOfInterest = {
            {{242, 549}, {244, 538}, {245, 529}},
            {{691, 915}, {673, 900}, {650, 901}},
        };
    }
    else if (m_level->name() == "level_13")
    {
        pointsOfInterest = {
            {{489, 360}, {477, 373}, {477, 341}, {489, 329}},
            {{498, 374}, {485, 369}, {469, 362}},
            {{826, 1310}, {876, 1282}, {873, 1260}},
            {{958, 1325}, {934, 1284}, {937, 1266}},
            {{895, 1297}, {896, 1283}, {898, 1268}},
            {{917, 1297}, {916, 1283}, {917, 1283}},
            {{759, 753}, {745, 745}, {729, 736}},
            {{764, 726}, {724, 767}, {724, 720}, {738, 692}, {764, 687}},
            {{766, 747}, {751, 750}, {736, 732}},
            {{739, 768}, {731, 757}, {720, 751}},
            {{746, 758}, {738, 750}, {729, 744}},
        };
    }
    else if (m_level->name() == "level_14")
    {
        pointsOfInterest = {
            {{738, 1006}, {732, 1012}, {726, 1019}},
            {{720, 1001}, {713, 1001}, {705, 1014}},
            {{757, 1010}, {755, 1017}, {749, 1023}},
            {{728, 1004}, {723, 1011}, {717, 1017}},
            {{754, 1005}, {747, 1013}, {739, 1021}},
        };
    }
    else if (m_level->name() == "level_15")
    {
        pointsOfInterest = {
            {{1796, 971}, {1788, 963}, {1788, 944}, {1796, 952}, {1796, 971}},
            {{1782, 971}, {1782, 971}, {1782, 971}},
            {{698, 776}, {712, 765}, {732, 758}},
            {{902, 716}, {881, 711}, {859, 717}},
            {{1490, 999}, {1491, 962}, {1495, 958}, {1504, 954}, {1508, 993}},
            {{1512, 1007}, {1500, 995}, {1490, 983}},
            {{1652, 963}, {1642, 954}, {1642, 917}, {1652, 927}},
            {{1629, 965}, {1649, 960}, {1665, 951}},
            {{702, 320}, {659, 334}, {659, 304}, {666, 289}, {678, 281}, {688, 279}, {698, 282}, {702, 290}},
            {{687, 327}, {682, 327}, {677, 319}},
            {{1799, 523}, {1799, 487}, {1811, 473}, {1828, 468}, {1839, 473}, {1840, 510}},
            {{1835, 529}, {1822, 516}, {1809, 501}},
            {{1840, 524}, {1829, 513}, {1806, 502}},
        };
    }
    else if (m_level->name() == "level_22")
    {
        pointsOfInterest = {
            {{1481, 1641}, {1455, 1646}, {1426, 1655}},
            {{655, 1286}, {638, 1298}, {620, 1311}},
            {{2414, 689}},
            {{1151, 762}},
            {{1694, 1207}},
            {{1796, 1172}},
            {{1785, 1143}},
            {{1802, 1186}},
            {{1717, 1243}},
            {{1772, 1221}},
            {{1717, 1238}},
            {{1861, 1186}},
            {{1660, 1279}},
        };
    }
    else if (m_level->name() == "level_23")
    {
        pointsOfInterest = {
            {{1288, 549}, {1296, 537}, {1310, 530}},
            {{1800, 626}},
            {{974, 1707}},
            {{1364, 497}},
            {{1310, 465}},
            {{1406, 518}},
        };
    }

    for (const auto& set : pointsOfInterest)
    {
        for (int i = 0; i < set.size(); ++i)
        {
            auto x1 = set[i].x;
            auto y1 = set[i].y;

            auto x2 =
                i + 1 < set.size()
                ? set[i + 1].x
                : set[0].x;

            auto y2 =
                i + 1 < set.size()
                ? set[i + 1].y
                : set[0].y;

            auto item = new QGraphicsLineItem(x1, y1, x2, y2);
            item->setPen(QPen(Qt::white));
            m_scene->addItem(item);
        }

        for (const auto& coord : set)
        {
            auto item = new QGraphicsRectItem(coord.x - 4, coord.y - 4, 8, 8);
            item->setBrush(QBrush(Qt::yellow));
            m_scene->addItem(item);
        }
    }
    */
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
