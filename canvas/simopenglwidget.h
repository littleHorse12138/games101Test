#ifndef SIMOPENGLWIDGET_H
#define SIMOPENGLWIDGET_H

#include <QWidget>
class Model;
class Camera;

class SimOpenglWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimOpenglWidget(QWidget *parent, Model* model, Camera* camera);
protected:
    void paintEvent(QPaintEvent* ev);
private:
    Model* m_pModel = nullptr;
    Camera* m_pCamera = nullptr;
};

#endif // SIMOPENGLWIDGET_H
