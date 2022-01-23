extern "C" {
#include "lib/level/level.h"
}

#include "app/level-editor/mapview.hh"
#include "app/level-editor/mainwindow.hh"
#include "lib/common/log.hh"

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>

#include <filesystem>
#include <iostream>

// -----------------------------------------------------------------------------

using d1::level_editor::MainWindow;

// -----------------------------------------------------------------------------

MainWindow::MainWindow(
)
    : QMainWindow(nullptr)
{
    m_fileMenu = new QMenu("File", this);
    m_openAction = new QAction("Open", this);
    m_fileMenu->addAction(m_openAction);
    menuBar()->addMenu(m_fileMenu);

    m_mapView = new MapView(this);
    setCentralWidget(m_mapView);

    connect(
        m_openAction,
        &QAction::triggered,
        this,
        &MainWindow::onOpenAction
    );
}

void MainWindow::onOpenAction(
)
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
        if (m_openLevel != nullptr)
        {
            D1Level_free(m_openLevel);
        }

        m_openLevel = D1Level_newFromDvdFile(filepath.toStdString().c_str());
        m_mapView->setLevel(m_openLevel);
        setWindowTitle(QString("d1-level-editor — ") + D1Level_name(m_openLevel));
        settings.setValue("LastOpenedDvdFile", filepath);
    }
}
