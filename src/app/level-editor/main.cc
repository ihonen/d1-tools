#include "app/level-editor/mainwindow.hh"

#include <QApplication>

#include <cstdlib>
#include <cstdio>
#include <iostream>

// -----------------------------------------------------------------------------

int main(
    int argc,
    char* argv[]
)
{
    QApplication qApplication(argc, argv);
    QApplication::setOrganizationName("d1-tools");
    QApplication::setOrganizationDomain("github.com/ihonen/d1-tools");
    QApplication::setApplicationName("d1-level-editor");
    
    d1::level_editor::MainWindow mainWindow;
    mainWindow.showMaximized();
    
    return qApplication.exec();
}
