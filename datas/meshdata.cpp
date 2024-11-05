#include "meshdata.h"
#include <QDebug>
MeshData::MeshData(Model *par)
{
    m_pPar = par;
}

Model *MeshData::pPar() const
{
    return m_pPar;
}

void MeshData::setPPar(Model *newPPar)
{
    m_pPar = newPPar;
}

VertexHandle *MeshData::addVertex(QVector3D pos)
{
    Vertex* v = new Vertex(pos);
    VertexHandle* handle = new VertexHandle;
    m_vertexMap.insert(handle, v);
    handle->setVertex(v);
    m_vertexHandleList.append(handle);
    return handle;
}

VertexHandle *MeshData::vertexHandle(int index)
{
    return m_vertexHandleList[index];
}

FaceHandle *MeshData::addFace(VertexHandle *v1, VertexHandle *v2, VertexHandle *v3)
{
    Face* face = new Face(v1,v2,v3);
    FaceHandle* handle = new FaceHandle;
    m_faceHandleList.append(handle);
    m_faceMap.insert(handle, face);
    return handle;
}

FaceHandle *MeshData::faceHandle(int index)
{
    return m_faceHandleList[index];
}

Face *MeshData::face(FaceHandle *handle)
{
    return m_faceMap[handle];
}

int MeshData::faceNum() const
{
    return m_faceNum;
}

QList<float> MeshData::getVertices()
{
    QList<float> vertices;
    for(auto handle: m_faceHandleList){
        auto face = m_faceMap[handle];
        for(int i = 0; i < 3; i++){
            auto vHandle = face->vh(i);
            auto v = m_vertexMap[vHandle];
            vertices.append(v->pos()[0]);
            vertices.append(v->pos()[1]);
            vertices.append(v->pos()[2]);
        }
    }
    qDebug() << "chufa end 11 " << vertices.size();
    return vertices;
}
