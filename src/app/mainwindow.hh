#pragma once

#include <QMainWindow>

// -----------------------------------------------------------------------------

#include "app/fwd.h"
#include "level/fwd.h"

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

        QDockWidget* m_dock = nullptr;
        MapView* m_mapView = nullptr;
        PropertyView* m_propertyView = nullptr;
        
        D1Level* m_openLevel = nullptr;
    };

}
