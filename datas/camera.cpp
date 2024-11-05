#include "camera.h"
#include "datas/model.h"
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
