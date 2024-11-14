#ifndef ONEMODELWIDGET_H
#define ONEMODELWIDGET_H

#include <QWidget>
#include "datas/model.h"
namespace Ui {
class OneModelWidget;
}

class OneModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OneModelWidget(Model* model, QWidget *parent = nullptr);
    ~OneModelWidget();
protected:
    void init();
    void connectSignalAndSlots();

    void onBtnExpandlicked();
    void onBtnShowOrHideClicked();
    void onBtnShowGridClicked();
    void onBtnShowBoundingBoxClicked();
    void onBtnLoopSubdivisionClicked();
private:
    Ui::OneModelWidget *ui;
    Model* m_pModel = nullptr;
};

#endif // ONEMODELWIDGET_H
