#include "app/mainwindow.hh"
#include "app/mapview.hh"
#include "app/propertyview.hh"
#include "common/log.hh"
#include "level/level.hh"

#include <QAction>
#include <QDockWidget>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>

#include <filesystem>
#include <iostream>

// -----------------------------------------------------------------------------

MainWindow::MainWindow()
    : QMainWindow(nullptr)
{
    m_fileMenu = new QMenu("File", this);
    m_openAction = new QAction("Open", this);
    m_fileMenu->addAction(m_openAction);
    menuBar()->addMenu(m_fileMenu);

    m_mapView = new MapView(this);
    setCentralWidget(m_mapView);

    m_dock = new QDockWidget(tr("Properties"), this);
    m_dock->setAllowedAreas(Qt::RightDockWidgetArea);
    m_propertyView = new PropertyView(m_dock);
    m_dock->setWidget(m_propertyView);
    addDockWidget(Qt::RightDockWidgetArea, m_dock);

    connect(
        m_openAction,
        &QAction::triggered,
        this,
        &MainWindow::onOpenAction
    );
}

void MainWindow::onOpenAction()
{
    QSettings settings;
    auto lastOpenedDvdFile = std::filesystem::path(
        settings.value("LastOpenedDvdFile").toString().toStdString()
    );
    auto lastOpenedDvdDir = lastOpenedDvdFile.parent_path();

    auto filepath = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        lastOpenedDvdDir.string().c_str(),
        tr("Level Files (*.dvd)")
    );

    if (filepath.length() > 0)
    {
        m_openLevel = std::make_shared<Level>(filepath.toStdString().c_str());
        m_mapView->setLevel(m_openLevel);
        setWindowTitle(QString("D1 Level Editor — ") + QString::fromStdString(m_openLevel->name()));
        settings.setValue("LastOpenedDvdFile", filepath);
    }
}
