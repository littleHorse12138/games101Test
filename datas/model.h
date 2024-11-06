#ifndef MODEL_H
#define MODEL_H
#include <QList>
#include "datas/meshdata.h"
#include "shaderprogram.h"
#include <QMatrix4x4>
#include "QOpenGLFunctions_3_3_Core"
class Model:public QOpenGLFunctions_3_3_Core
{
public:
    Model();
    MeshData *pMesh() const;
    void setPMesh(MeshData *newPMesh);

    ShaderProgram *pShader() const;
    void setPShader(ShaderProgram *newPShader);

    void setMatrix(QMatrix4x4 mat);
    QMatrix4x4 getMatrix();

    void updateMeshToShader();
    QList<Model *> children() const;
    void setChildren(const QList<Model *> &newChildren);

    int nodeMask() const;
    void setNodeMask(int newNodeMask);

    void addChild(Model* child);

    unsigned int vao() const;
    void setVao(unsigned int newVao);

protected:
    void init();
private:
    QList <Model*> m_children;
    Model* m_pParent = nullptr;

    int m_nodeMask = 1;
    QMatrix4x4 m_matrix;

    MeshData* m_pMesh = nullptr;
    ShaderProgram* m_pShader = nullptr;

    unsigned int m_vao = -1;
    unsigned int m_vbo = -1;
};

#endif // MODEL_H
