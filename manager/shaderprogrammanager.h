#ifndef SHADERPROGRAMMANAGER_H
#define SHADERPROGRAMMANAGER_H

#include <QObject>
#include "datas/viewer.h"
#include "datas/shaderprogram.h"
class Model;
class ShaderProgramManager : public QObject
{
    Q_OBJECT
public:
    explicit ShaderProgramManager(QObject *parent = nullptr);
    static ShaderProgramManager* getInstance();

    void bindToBlingPhoneShader(Model* model, Viewer* camera);
protected:
    void init();

    void setShaderInitData(Model* model);
private:
signals:
};

#define SM ShaderProgramManager::getInstance()
#endif // SHADERPROGRAMMANAGER_H
