#include "headers/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.resize(800 * 16/9,600);
    w.setWindowTitle("IOT Monitoring");
    w.show();

    return app.exec();
}
