#pragma once

#include <QMainWindow>

#include <memory>

// -----------------------------------------------------------------------------

class Level;

class InfoView;
class MapView;
class PropertyView;

class QAction;
class QMenu;
class QTextBrowser;

// -----------------------------------------------------------------------------

class MainWindow
    : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow();

private:

    void closeEvent(QCloseEvent* event) override;

    void onOpenAction();

    QMenu* m_fileMenu = nullptr;
    QAction* m_openAction = nullptr;

    MapView* m_mapView = nullptr;

    QDockWidget* m_propertyDock = nullptr;
    PropertyView* m_propertyView = nullptr;

    QDockWidget* m_logDock = nullptr;
    InfoView* m_infoView = nullptr;
    
    QStatusBar* m_statusBar = nullptr;

    std::shared_ptr<Level> m_openLevel = nullptr;
};
