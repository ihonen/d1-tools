#include "app/level-editor/mainwindow.hh"

#include <QApplication>

#include <cstdlib>
#include <iostream>

// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    QApplication qApplication(argc, argv);
    
    d1::level_editor::MainWindow mainWindow;
    mainWindow.show();
    
    return qApplication.exec();
}
