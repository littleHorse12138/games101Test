#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>

namespace Ui {
class ToolWidget;
}

class ToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolWidget(QWidget *parent = nullptr);
    ~ToolWidget();

private:
    Ui::ToolWidget *ui;
};

#endif // TOOLWIDGET_H
