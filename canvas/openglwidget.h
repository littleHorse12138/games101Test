#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <qopenglfunctions_3_3_core.h>
#include "datas/camera.h"
class Model;
class OpenglWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenglWidget(QWidget *parent = nullptr);
    static OpenglWidget* getInstance();

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void showEvent(QShowEvent* ev);
    Camera *pCamera() const;
    void setPCamera(Camera *newPCamera);

protected:
    void drawModel(Model* model);

protected:
    void init();

    void testInit(); //仅测试用
private:
    Camera* m_pCamera = nullptr;
};
#define OW OpenglWidget::getInstance()
#endif // OPENGLWIDGET_H
