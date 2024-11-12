#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas/openglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void init();
    void connectSignalAndSlots();
private:
    Ui::MainWindow *ui;
    OpenglWidget* m_pOpenglWidget = nullptr;
};
#endif // MAINWINDOW_H
