#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QMatrix4x4>
class Model;
class Camera
{
public:
    Camera();

    QMatrix4x4 getViewMatrix();
    QMatrix4x4 getPerspectiveMatrix();
    void widgetScaleChanged(float w, float h);

    void addModel(Model* model);
    QVector3D cameraPos() const;
    void setCameraPos(const QVector3D &newCameraPos);

    void moveFront();
    void moveBack();
protected:
    void updateCameraData();
private:
    QVector3D m_cameraPos = QVector3D(0, 0, -30);
    QVector3D m_cameraFront = QVector3D(0, 0, 0);
    QVector3D m_cameraUp = QVector3D(0, 1, 0);

    QMatrix4x4 m_perspectiveMatrix;
    QList <Model*> m_models;
};

#endif // CAMERA_H
