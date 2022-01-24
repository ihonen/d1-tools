#pragma once

#include <QMainWindow>

#include <memory>

// -----------------------------------------------------------------------------

class Level;
class MapView;
class PropertyView;

class QAction;
class QMenu;

// -----------------------------------------------------------------------------

class MainWindow
    : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow();

private:

    void onOpenAction();

    QMenu* m_fileMenu = nullptr;
    QAction* m_openAction = nullptr;

    QDockWidget* m_dock = nullptr;
    MapView* m_mapView = nullptr;
    PropertyView* m_propertyView = nullptr;
        
    std::shared_ptr<Level> m_openLevel = nullptr;
};
