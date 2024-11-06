#ifndef FPSWIDGET_H
#define FPSWIDGET_H

#include <QWidget>
#include <QTimer>
namespace Ui {
class FpsWidget;
}
class OpenglWidget;
class FpsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FpsWidget(OpenglWidget* openglWgt, QWidget *parent = nullptr);
    ~FpsWidget();
protected:
    void init();

    void onTimerUpdateTimeout();
private:
    Ui::FpsWidget *ui;
    QTimer* m_pUpdateTimer = nullptr;
    OpenglWidget* m_pParWgt = nullptr;
};

#endif // FPSWIDGET_H
