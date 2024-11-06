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

Material *MaterialManager::getRubberMaterial()
{
    return m_materials[0];
}

void MaterialManager::init()
{
    m_materials.append(new MaterialRubber());
}

void MaterialManager::updateMaterialDataToShader(Model* model)
{
    auto m = model->pMesh()->material();
    model->pShader()->setVec3("specular", m->specular());
    model->pShader()->setFloat("shininess", m->shininess());
}
