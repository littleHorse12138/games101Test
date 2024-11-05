#include "mainwindow.h"

#include <QApplication>
#include "canvas/openglwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    OpenglWidget w;
    w.show();
    return a.exec();
}
