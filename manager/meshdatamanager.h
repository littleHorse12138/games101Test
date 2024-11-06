#ifndef MESHDATAMANAGER_H
#define MESHDATAMANAGER_H

#include <QObject>
#include "datas/meshdata.h"
#include "datas/model.h"
class MeshDataManager : public QObject
{
    Q_OBJECT
public:
    explicit MeshDataManager(QObject *parent = nullptr);
    static MeshDataManager* getInstance();
    void writeMesh(MeshData* data, QString path);
    bool readMesh(MeshData* data, QString path);

    void addModel(Model* model);
    Model *root() const;
    void setRoot(Model *newRoot);

    int getAllRenderPointNum(Model* model);
protected:
    void init();
    bool readObj(MeshData* data, QString path);
private:
    QList <Model*> m_models;
    Model* m_root;
signals:
};
#define MDM MeshDataManager::getInstance()
#endif // MESHDATAMANAGER_H
