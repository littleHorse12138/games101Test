#include "materialmanager.h"
MaterialManager::MaterialManager(QObject *parent)
    : QObject{parent}
{
    init();
}

MaterialManager *MaterialManager::getInstance()
{
    static MaterialManager* instance = nullptr;
    if(!instance){
        instance = new MaterialManager;
    }
    return instance;
}

void MaterialManager::bindModelToRubberMaterial(Model* model)
{
    model->pMesh()->setMaterial(getRubberMaterial());
    updateMaterialDataToShader(model);
}

void MaterialManager::bindModelToStainlessSteelMaterial(Model *model)
{
    model->pMesh()->setMaterial(getStainlessSteelMaterial());
    updateMaterialDataToShader(model);
}

Material *MaterialManager::getRubberMaterial()
{
    return m_materials[0];
}

Material *MaterialManager::getStainlessSteelMaterial()
{
    return m_materials[1];
}

void MaterialManager::init()
{
    m_materials.append(new MaterialRubber());
    m_materials.append(new MaterialStainlessSteel());
}

void MaterialManager::updateMaterialDataToShader(Model* model)
{
    auto m = model->pMesh()->material();
    model->pShader()->use();
    model->pShader()->setVec3("materialSpecular", m->specular());
    model->pShader()->setFloat("materialShininess", m->shininess());
    model->pShader()->setVec3("materialDiffuse", m->diffuse());
    model->pShader()->setVec3("materialAmbient", m->ambient());
}
