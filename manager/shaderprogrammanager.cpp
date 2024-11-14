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

void ShaderProgramManager::bindToBlingPhoneShader(Model *model, Viewer *viewer)
{
    auto newBling = new BlingPhoneShader();
    model->setPShader(newBling);
    setShaderInitData(model);
    viewer->bindToViewer(model);

    if(model->pPolygonModel()){
        bindToBlingPhoneShader(model->pPolygonModel(), viewer);
    }
}


void ShaderProgramManager::init()
{

}

void ShaderProgramManager::setShaderInitData(Model* model)
{
    model->setMatrix(model->getMatrix());
}
