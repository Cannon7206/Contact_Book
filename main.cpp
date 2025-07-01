#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //start application
    QApplication app(argc, argv);
    //create window
    MainWindow window;
    //show window
    window.show();
    return app.exec();
}
