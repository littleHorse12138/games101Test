#include "camera.h"
#include "datas/model.h"
#include <canvas/simopenglwidget.h>
Camera::Camera() {}

QMatrix4x4 Camera::getViewMatrix()
{
    QMatrix4x4 view;
    view.lookAt(m_cameraPos, m_cameraFront, m_cameraUp);
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
    qDebug() << "chufa!!@@";
    // auto dir = (m_cameraFront - m_cameraPos);
    auto dir = QVector3D(1,0,0);
    dir.normalize();
    // m_cameraPos += dir * 5.5;
    updateCameraData();
}

void Camera::moveBack()
{
    // auto dir = (m_cameraFront - m_cameraPos);
    auto dir = QVector3D(1,0,0);
    dir.normalize();
    // m_cameraPos -= dir * 5.5;
    updateCameraData();
}

void Camera::updateCameraData()
{
    for(auto model: m_models){
        if(model->pShader()){
            qDebug() << "inside;" << m_cameraPos;
            model->pShader()->use();
            model->pShader()->setMatrix("view", getViewMatrix());
            model->pShader()->setVec3("viewPos", cameraPos());
            model->pShader()->unUse();

            SimOpenglWidget* wgt = new SimOpenglWidget(nullptr, model, this);
            wgt->show();
        }
    }

    QVector3D p(1,0,0);
    QMatrix4x4 m;
    m.translate(QVector3D(0, 5, 0));
    qDebug() << "test" << p*m << getPerspectiveMatrix()*getViewMatrix()*p;

}
