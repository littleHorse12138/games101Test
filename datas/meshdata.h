#ifndef MESHDATA_H
#define MESHDATA_H
#include "datas/face.h"
#include "datas/facehandle.h"
#include "vertex.h"
#include "datas/vertexhandle.h"

#include <QList>
#include <QMap>
class Model;
class Material;
class MeshData
{
public:
    MeshData(Model* par = nullptr);

    Model *pPar() const;
    void setPPar(Model *newPPar);

    VertexHandle* addVertex(QVector3D pos);
    VertexHandle* vertexHandle(int index);

    FaceHandle* addFace(VertexHandle* v1, VertexHandle* v2, VertexHandle* v3);
    FaceHandle* faceHandle(int index);

    Face* face(FaceHandle* handle);
    Vertex* vertex(VertexHandle* handle);

    int faceNum() const;

    QList <float> getVertices();
    int vertexNum() const;

    //拓扑关系
    QList <FaceHandle*> getBoundingFace(VertexHandle* vh);

    //法向量
    QVector3D normal(VertexHandle* vh);
    QVector3D normal(FaceHandle* vh);
    Material *material() const;
    void setMaterial(Material *newMaterial);

private:
    Model* m_pPar = nullptr;

    QMap<FaceHandle*, Face*> m_faceMap;
    QList <FaceHandle*> m_faceHandleList;

    QMap<VertexHandle*, Vertex*> m_vertexMap;
    QList <VertexHandle*> m_vertexHandleList;

    int m_faceNum = 0;
    int m_vertexNum = 0;

    //相邻关系
    QMap <VertexHandle*, QList <FaceHandle*>> m_vertexAndBoundFaceMap;

    Material* m_material;
};

#endif // MESHDATA_H
