#include "app/mainwindow.hh"

#include <QApplication>

#include <cstdlib>
#include <cstdio>
#include <iostream>

// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    QApplication qApplication(argc, argv);
    QApplication::setOrganizationName("d1-tools");
    QApplication::setOrganizationDomain("github.com/ihonen/d1-tools");
    QApplication::setApplicationName("D1 Level Viewer");
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return qApplication.exec();
}
