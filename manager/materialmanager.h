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
    void bindModelToStainlessSteelMaterial(Model* model);
    void updateMaterialDataToShader(Model* model);
protected:
    void init();

    Material* getRubberMaterial();
    Material* getStainlessSteelMaterial();
private:
    QList <Material*> m_materials;
};
#define MM MaterialManager::getInstance()
#endif // MATERIALMANAGER_H
