#ifndef ONEMODELWIDGET_H
#define ONEMODELWIDGET_H

#include <QWidget>

namespace Ui {
class OneModelWidget;
}

class OneModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OneModelWidget(QWidget *parent = nullptr);
    ~OneModelWidget();

private:
    Ui::OneModelWidget *ui;
};

#endif // ONEMODELWIDGET_H
