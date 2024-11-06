#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <qopenglfunctions_3_3_core.h>
#include "datas/camera.h"
class Model;
class Light;
class OpenglWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenglWidget(QWidget *parent = nullptr);
    static OpenglWidget* getInstance();

    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    Camera *pCamera() const;
    void setPCamera(Camera *newPCamera);

protected:
    void drawModel(Model* model);

    virtual void showEvent(QShowEvent* ev) override;
    virtual void mousePressEvent(QMouseEvent* ev) override;
    virtual void mouseMoveEvent(QMouseEvent* ev) override;
    virtual void mouseReleaseEvent(QMouseEvent* ev) override;
    virtual void wheelEvent(QWheelEvent* ev) override;
protected:
    void init();

    void testInit(); //仅测试用
private:
    Camera* m_pCamera = nullptr;
    Light* m_pLight = nullptr;

};
#define OW OpenglWidget::getInstance()
#endif // OPENGLWIDGET_H
