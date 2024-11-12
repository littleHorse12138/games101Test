#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <qopenglfunctions_3_3_core.h>
#include "datas/camera.h"
#include "fpswidget.h"
#include <QTimer>
class Model;
class Light;
class Viewer;
class OpenglWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenglWidget(QWidget *parent = nullptr);
    static OpenglWidget* getInstance();

    int updateTimeSinceLastUpdate() const;

    void setUpdateTimeSinceLastUpdate(int newUpdateTimeSinceLastUpdate);

    void buildNewModel();
protected:
    void drawModel(Model* model);

    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    virtual void showEvent(QShowEvent* ev) override;
    virtual void mousePressEvent(QMouseEvent* ev) override;
    virtual void mouseMoveEvent(QMouseEvent* ev) override;
    virtual void mouseReleaseEvent(QMouseEvent* ev) override;
    virtual void wheelEvent(QWheelEvent* ev) override;

    void init();
    void testInit(); //仅测试用

    void onTimerUpdateTimeout();
private:
    Viewer* m_pViewer = nullptr;
    Light* m_pLight = nullptr;

    QPoint m_lastMousePlace;
    QTimer* m_pUpdateTimer = nullptr;

    int m_updateTimeSinceLastUpdate = 0;

    FpsWidget* m_pFpsWidget = nullptr;
};
#define OW OpenglWidget::getInstance()
#endif // OPENGLWIDGET_H
