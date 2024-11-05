#ifndef MESHDATA_H
#define MESHDATA_H
#include "datas/face.h"
#include "datas/facehandle.h"
#include "vertex.h"
#include "datas/vertexhandle.h"

#include <QList>
#include <QMap>
class Model;
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
private:
    Model* m_pPar = nullptr;

    QMap<FaceHandle*, Face*> m_faceMap;
    QList <FaceHandle*> m_faceHandleList;

    QMap<VertexHandle*, Vertex*> m_vertexMap;
    QList <VertexHandle*> m_vertexHandleList;

    int m_faceNum = 0;
};

#endif // MESHDATA_H
