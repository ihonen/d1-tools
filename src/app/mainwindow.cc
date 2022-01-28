#include "app/infoview.hh"
#include "app/mainwindow.hh"
#include "app/levelview.hh"
#include "app/propertyview.hh"
#include "common/log.hh"
#include "world/level.hh"

#include <QAction>
#include <QDockWidget>
#include <QFileDialog>
#include <QFormLayout>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QShortcut>
#include <QStatusBar>
#include <QTextBrowser>

#include <filesystem>
#include <iostream>

// -----------------------------------------------------------------------------

MainWindow::MainWindow()
    : QMainWindow(nullptr)
{
    m_statusBar = new QStatusBar(this);
    setStatusBar(m_statusBar);

    m_fileMenu = new QMenu("File", this);
    m_openAction = new QAction("Open", this);
    m_fileMenu->addAction(m_openAction);
    menuBar()->addMenu(m_fileMenu);

    m_levelView = new LevelView(this);
    setCentralWidget(m_levelView);

    m_propertyDock = new QDockWidget(tr("Properties"), this);
    m_propertyDock->setAllowedAreas(Qt::RightDockWidgetArea);
    m_propertyDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    m_propertyView = new PropertyView(m_propertyDock);
    m_propertyDock->setWidget(m_propertyView);
    addDockWidget(Qt::RightDockWidgetArea, m_propertyDock);

    m_logDock = new QDockWidget(tr(""), this);
    m_logDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    m_logDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    m_infoView = new InfoView(m_logDock);
    m_logDock->setWidget(m_infoView);
    addDockWidget(Qt::LeftDockWidgetArea, m_logDock);

    connect(
        m_openAction,
        &QAction::triggered,
        this,
        &MainWindow::onOpenAction
    );

    connect(
        m_levelView,
        &LevelView::mousePositionChanged,
        [this](auto x, auto y)
        {
            m_statusBar->showMessage(QString("%1, %2").arg(x).arg(y));
        }
    );

    connect(
        m_levelView,
        &LevelView::worldItemHovered,
        m_infoView,
        &InfoView::displayWorldItem
    );

    new QShortcut(
        QKeySequence("F1"),
        this,
        [this]() { m_levelView->setMapVisible(!m_levelView->isMapVisible()); }
    );

    new QShortcut(
        QKeySequence("F2"),
        this,
        [this]() { m_levelView->setBuildingsVisible(!m_levelView->isBuildingsVisible()); }
    );

    new QShortcut(
        QKeySequence("F3"),
        this,
        [this]() { m_levelView->setMaterialsVisible(!m_levelView->isMaterialsVisible()); }
    );

    QSettings settings;
    restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
    restoreState(settings.value("MainWindow/state").toByteArray());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings;
    settings.setValue("MainWindow/geometry", saveGeometry());
    settings.setValue("MainWindow/state", saveState());
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
        m_levelView->setLevel(m_openLevel);
        setWindowTitle(QString("D1 Level Editor — ") + QString::fromStdString(m_openLevel->name()));
        settings.setValue("LastOpenedDvdFile", filepath);
    }
}
