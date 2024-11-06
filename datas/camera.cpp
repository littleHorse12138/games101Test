#include "camera.h"
#include "datas/model.h"
#include <canvas/simopenglwidget.h>
#include "tool/tool.h"
Camera::Camera() {}

QMatrix4x4 Camera::getViewMatrix()
{
    QMatrix4x4 view;
    view.lookAt(m_cameraPos, m_cameraViewPoint, m_cameraUp);
    return view;
}

QMatrix4x4 Camera::getPerspectiveMatrix()
{
    return m_perspectiveMatrix;
}

void Camera::widgetScaleChanged(float w, float h)
{
    float aspect = w / h;
    m_perspectiveMatrix = QMatrix4x4();
    m_perspectiveMatrix.perspective(45.0f, aspect, 0.1f, 100.0f);
    for(auto model: m_models){
        if(model->pShader()){
            model->pShader()->setMatrix("projection", m_perspectiveMatrix);
        }
    }
}

void Camera::addModel(Model *model)
{
    m_models.append(model);
}

QVector3D Camera::cameraPos() const
{
    return m_cameraPos;
}

void Camera::setCameraPos(const QVector3D &newCameraPos)
{
    m_cameraPos = newCameraPos;
}

void Camera::moveFront()
{
    auto dir = m_cameraViewPoint - m_cameraPos;
    dir.normalize();
    float moveDis = 1.5;
    m_cameraPos += dir * moveDis;
    m_cameraViewPoint += dir * moveDis;
    updateCameraData();
}

void Camera::moveBack()
{
    auto dir = m_cameraViewPoint - m_cameraPos;
    dir.normalize();
    float moveDis = -1.5;
    m_cameraPos += dir * moveDis;
    m_cameraViewPoint += dir * moveDis;
    updateCameraData();
}

void Camera::moveTranslate(QPoint p)
{
    auto cameraFront = m_cameraViewPoint - m_cameraPos;
    cameraFront.normalize();

    auto right =cameraRight();

    auto tran1 = right * p.x();
    auto tran2 = m_cameraUp * p.y();

    float moveSpeed = 0.1;
    m_cameraPos += (tran1 + tran2) * moveSpeed;
    m_cameraViewPoint += (tran1 + tran2) * moveSpeed;
    updateCameraData();
}

void Camera::moveRotate(QPoint p)
{
    // auto nowViewPoint = m_cameraViewPoint;

    // m_cameraViewPoint -= nowViewPoint;
    // m_cameraPos -= nowViewPoint;

    // float rotateSpeed = 0.1;
    // QMatrix4x4 rotMat1, rotMat2;
    // rotMat1.rotate(rotateSpeed * p.x(), m_cameraUp);

    // m_cameraPos = rotMat1 * m_cameraPos;
    // m_cameraUp = rotMat1 * m_cameraUp;

    // rotMat2.rotate(rotateSpeed * p.y(), cameraRight());
    // m_cameraPos = rotMat2 * m_cameraPos;
    // m_cameraUp = rotMat2 * m_cameraUp;


    // m_cameraViewPoint += nowViewPoint;
    // m_cameraPos += nowViewPoint;

    float rotateSpeed = 0.1;
    m_cameraPos -= m_cameraViewPoint;

    auto rotAxis = -1 * m_cameraUp * p.x() + cameraRight() * p.y() * 1;
    rotAxis.normalize();

    QMatrix4x4 rotMat1;
    rotMat1.rotate(rotateSpeed * Tool::length(p), rotAxis);
    m_cameraPos = rotMat1 * m_cameraPos;
    m_cameraUp = rotMat1 * m_cameraUp;

    m_cameraPos += m_cameraViewPoint;

    updateCameraData();


}

QVector3D Camera::cameraFront()
{
    auto dir = m_cameraViewPoint - m_cameraPos;
    dir.normalize();
    return dir;
}

QVector3D Camera::cameraRight()
{
    auto right = -1 * cameraFront().crossProduct(cameraFront(), m_cameraUp);
    right.normalize();
    return right;
}

void Camera::updateCameraData()
{
    for(auto model: m_models){
        if(model->pShader()){
            model->pShader()->use();
            model->pShader()->setMatrix("view", getViewMatrix());
            model->pShader()->setVec3("viewPos", cameraPos());
            model->pShader()->unUse();
        }
    }

}
