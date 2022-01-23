#pragma once

#include <QMainWindow>

// -----------------------------------------------------------------------------

#include "app/level-editor/fwd.h"
#include "lib/level/fwd.h"

class QAction;
class QMenu;

// -----------------------------------------------------------------------------

namespace d1::level_editor
{

    class MainWindow
        : public QMainWindow
    {
        Q_OBJECT
    public:

        MainWindow(
        );

    private:

        void onOpenAction();

        QMenu* m_fileMenu = nullptr;
        QAction* m_openAction = nullptr;

        MapView* m_mapView = nullptr;
        
        D1Level* m_openLevel = nullptr;
    };

}
