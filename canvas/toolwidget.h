#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>

namespace Ui {
class ToolWidget;
}
class OpenglWidget;
class ToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolWidget(QWidget *parent = nullptr);
    ~ToolWidget();


    OpenglWidget *pOpenglWidget() const;
    void setPOpenglWidget(OpenglWidget *newPOpenglWidget);

protected:
    void init();
    void connectSignalAndSlots();

    void onBtnSimShaderClicked();
private:
    Ui::ToolWidget *ui;
    OpenglWidget* m_pOpenglWidget = nullptr;
};

#endif // TOOLWIDGET_H
