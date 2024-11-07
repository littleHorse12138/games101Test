#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QMatrix4x4>
#include <QObject>
class Model;
class Camera: public QObject
{
    Q_OBJECT
public:
    Camera();

    QMatrix4x4 getViewMatrix();
    QMatrix4x4 getPerspectiveMatrix();
    void widgetScaleChanged(float w, float h);

    QVector3D cameraPos() const;
    void setCameraPos(const QVector3D &newCameraPos);

    void moveFront();
    void moveBack();
    void moveTranslate(QPoint p);
    void moveRotate(QPoint p);

    QVector3D cameraFront();
    QVector3D cameraRight();
protected:
private:
    QVector3D m_cameraPos = QVector3D(0, 0, -30);
    QVector3D m_cameraViewPoint = QVector3D(0, 0, 0);
    QVector3D m_cameraUp = QVector3D(0, 1, 0);

    QMatrix4x4 m_perspectiveMatrix;

signals:
    void sgCameraMove();
    void sgCameraPerspectiveChanged();
};

#endif // CAMERA_H
