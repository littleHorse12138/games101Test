#include "shaderprogrammanager.h"
#include "datas/model.h"
ShaderProgramManager::ShaderProgramManager(QObject *parent)
    : QObject{parent}
{
    init();
}

ShaderProgramManager *ShaderProgramManager::getInstance()
{
    static ShaderProgramManager* instance = nullptr;
    if(!instance){
        instance = new ShaderProgramManager;
    }
    return instance;
}

void ShaderProgramManager::bindToBlingPhoneShader(Model *model, Camera *camera)
{
    camera->addModel(model);
    auto newBling = new BlingPhoneShader();
    model->setPShader(newBling);
    setShaderInitData(model);
    newBling->setMatrix("view", camera->getViewMatrix());
    newBling->setMatrix("projection", camera->getPerspectiveMatrix());
}


void ShaderProgramManager::init()
{

}

void ShaderProgramManager::setShaderInitData(Model* model)
{
    model->setMatrix(model->getMatrix());
}
