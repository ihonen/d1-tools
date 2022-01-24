#include <QGraphicsView>

// -----------------------------------------------------------------------------

#include "level/fwd.h"

class QGraphicsScene;

// -----------------------------------------------------------------------------

namespace d1::level_editor
{

    class MapView
        : public QGraphicsView
    {
        Q_OBJECT
    public:

        MapView(
            QWidget* parent = nullptr
        );

        void setLevel(
            D1Level* level
        );

    private:

        QGraphicsScene* m_scene = nullptr;
        D1Level*        m_level = nullptr;
    };

}
