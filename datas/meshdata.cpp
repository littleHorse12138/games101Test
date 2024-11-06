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
    m_vertexNum++;
    return handle;
}

VertexHandle *MeshData::vertexHandle(int index)
{
    if(index >= m_vertexHandleList.size()){
        qDebug() << "no way";
    }
    return m_vertexHandleList[index];
}

FaceHandle *MeshData::addFace(VertexHandle *v1, VertexHandle *v2, VertexHandle *v3)
{
    Face* face = new Face(v1,v2,v3);
    FaceHandle* handle = new FaceHandle;
    m_faceHandleList.append(handle);
    m_faceMap.insert(handle, face);
    m_faceNum++;

    m_vertexAndBoundFaceMap[v1].append(handle);
    m_vertexAndBoundFaceMap[v2].append(handle);
    m_vertexAndBoundFaceMap[v3].append(handle);
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
            auto n = normal(vHandle);
            vertices.append(n[0]);
            vertices.append(n[1]);
            vertices.append(n[2]);
            vertices.append(1);
            vertices.append(0);
            vertices.append(1);
        }
    }
    return vertices;
}

int MeshData::vertexNum() const
{
    return m_vertexNum;
}

QList<FaceHandle *> MeshData::getBoundingFace(VertexHandle *vh)
{
    return m_vertexAndBoundFaceMap[vh];
}

QVector3D MeshData::normal(VertexHandle *vh)
{
    auto list = getBoundingFace(vh);
    int l = list.size();
    float areaAll = 0;
    QList <float> areaEach;
    for(int i = 0; i < l; i++){
        float a = face(list[i])->area();
        areaAll += a;
        areaEach.append(a);
    }
    QVector3D vN(0,0,0);
    for(int i = 0; i < l; i++){
        auto normal = face(list[i])->normal();
        vN = vN + (areaEach[i]/areaAll)*normal;
    }
    vN.normalize();
    return vN;
}

QVector3D MeshData::normal(FaceHandle *vh)
{
    return m_faceMap[vh]->normal();
}

Material *MeshData::material() const
{
    return m_material;
}

void MeshData::setMaterial(Material *newMaterial)
{
    m_material = newMaterial;
}
