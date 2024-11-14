#include "viewer.h"
#include "datas/light.h"
#include "datas/camera.h"
#include "datas/model.h"
#include "manager/materialmanager.h"
Viewer::Viewer(OpenglWidget* wgt) {
    m_pParWgt = wgt;
    init();
}

Camera *Viewer::pCamera() const
{
    return m_pCamera;
}

void Viewer::setPCamera(Camera *newPCamera)
{
    m_pCamera = newPCamera;
}

Light *Viewer::pLight() const
{
    return m_pLight;
}

void Viewer::setPLight(Light *newPLight)
{
    m_pLight = newPLight;
}

void Viewer::init()
{
    m_pCamera = new Camera;
    m_pLight = new Light;

    connect(m_pCamera, &Camera::sgCameraMove, this, &Viewer::onCameraMoved);
    connect(m_pCamera, &Camera::sgCameraPerspectiveChanged, this, &Viewer::onCameraPerspectiveChanged);
    connect(m_pLight, &Light::sgLightChanged, this, &Viewer::onLightChanged);
}

void Viewer::onLightChanged()
{
    for(auto model: m_models){
        auto shader = model->pShader();
        shader->setVec3("lightPos", m_pLight->lightPos());
        shader->setVec3("lightColor", m_pLight->lightColor());
    }
}

void Viewer::onCameraMoved()
{
    for(auto model: m_models){
        auto shader = model->pShader();
        shader->setMatrix("view", m_pCamera->getViewMatrix());
        shader->setVec3("viewPos", m_pCamera->cameraPos());
    }
}

void Viewer::onCameraPerspectiveChanged()
{
    for(auto model: m_models){
        auto shader = model->pShader();
        shader->setMatrix("projection", m_pCamera->getPerspectiveMatrix());
    }
}

void Viewer::updateAllDataToShader(Model* model)
{
    auto shader = model->pShader();
    if(!shader){
        return;
    }
    model->setMatrix(model->getMatrix());
    shader->setMatrix("view", m_pCamera->getViewMatrix());
    shader->setMatrix("projection", m_pCamera->getPerspectiveMatrix());
    shader->setVec3("lightPos", m_pLight->lightPos());
    shader->setVec3("viewPos", m_pCamera->cameraPos());
    shader->setVec3("lightColor", m_pLight->lightColor());
    auto m = model->pMesh()->material();
    model->pShader()->setVec3("materialSpecular", m->specular());
    model->pShader()->setFloat("materialShininess", m->shininess());
    model->pShader()->setVec3("materialDiffuse", m->diffuse());
    model->pShader()->setVec3("materialAmbient", m->ambient());

    if(model->pPolygonModel()){
        updateAllDataToShader(model->pPolygonModel());
    }
}

OpenglWidget *Viewer::pParWgt() const
{
    return m_pParWgt;
}

void Viewer::setPParWgt(OpenglWidget *newPParWgt)
{
    m_pParWgt = newPParWgt;
}

void Viewer::bindToViewer(Model *model)
{
    m_models.append(model);
    updateAllDataToShader(model);
}
