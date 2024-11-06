#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <QObject>
#include "datas/material.h"
#include "datas/model.h"
class Model;
class MaterialManager : public QObject
{
    Q_OBJECT
public:
    explicit MaterialManager(QObject *parent = nullptr);
    static MaterialManager* getInstance();

    void bindModelToRubberMaterial(Model* model);
protected:
    void init();

    void updateMaterialDataToShader(Model* model);
    Material* getRubberMaterial();
private:
    QList <Material*> m_materials;
};
#define MM MaterialManager::getInstance()
#endif // MATERIALMANAGER_H
