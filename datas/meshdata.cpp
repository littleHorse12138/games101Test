#include "meshdata.h"
#include <QDebug>
#include "datas/boundingbox.h"
MeshData::MeshData(Model *par)
{
    m_pPar = par;
    init();
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

    {
        auto edgeHandle = findEdge(v1, v2);
        if(!edgeHandle){
            Edge* edge = new Edge(v1, v2);
            edgeHandle = new EdgeHandle;
            m_edgeHandleList.append(edgeHandle);
            m_edgeMap.insert(edgeHandle, edge);
            m_vertexAndBoundVertexMap[v1].append(v2);
            m_vertexAndBoundVertexMap[v2].append(v1);
            m_vertexAndBoundEdgeMap[v1].append(edgeHandle);
            m_vertexAndBoundEdgeMap[v2].append(edgeHandle);
            m_edgeAndBoundFaceMap[edgeHandle].append(handle);
        }else{
            m_edgeAndBoundFaceMap[edgeHandle].append(handle);
        }
        m_faceAndBoundEdgeMap[handle].append(edgeHandle);
    }
    {
        auto edgeHandle = findEdge(v1, v3);
        if(!edgeHandle){
            Edge* edge = new Edge(v1, v3);
            edgeHandle = new EdgeHandle;
            m_edgeHandleList.append(edgeHandle);
            m_edgeMap.insert(edgeHandle, edge);
            m_vertexAndBoundVertexMap[v1].append(v3);
            m_vertexAndBoundVertexMap[v3].append(v1);
            m_vertexAndBoundEdgeMap[v1].append(edgeHandle);
            m_vertexAndBoundEdgeMap[v3].append(edgeHandle);
            m_edgeAndBoundFaceMap[edgeHandle].append(handle);
        }else{
            m_edgeAndBoundFaceMap[edgeHandle].append(handle);
        }
        m_faceAndBoundEdgeMap[handle].append(edgeHandle);
    }
    {
        auto edgeHandle = findEdge(v2, v3);
        if(!edgeHandle){
            Edge* edge = new Edge(v2, v3);
            edgeHandle = new EdgeHandle;
            m_edgeHandleList.append(edgeHandle);
            m_edgeMap.insert(edgeHandle, edge);
            m_vertexAndBoundVertexMap[v2].append(v3);
            m_vertexAndBoundVertexMap[v3].append(v2);
            m_vertexAndBoundEdgeMap[v2].append(edgeHandle);
            m_vertexAndBoundEdgeMap[v3].append(edgeHandle);
            m_edgeAndBoundFaceMap[edgeHandle].append(handle);
        }else{
            m_edgeAndBoundFaceMap[edgeHandle].append(handle);
        }
        m_faceAndBoundEdgeMap[handle].append(edgeHandle);
    }
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

Vertex *MeshData::vertex(VertexHandle *handle)
{
    return m_vertexMap[handle];
}

Edge *MeshData::edge(EdgeHandle *handle)
{
    return m_edgeMap[handle];
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
            auto c = color(handle);
            vertices.append(c[0]);
            vertices.append(c[1]);
            vertices.append(c[2]);
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

QList<EdgeHandle *> MeshData::getBoundingEdge(VertexHandle *vh)
{
    return m_vertexAndBoundEdgeMap[vh];
}

QList<VertexHandle *> MeshData::getBoundingVertex(VertexHandle *vh)
{
    return m_vertexAndBoundVertexMap[vh];
}

QList<FaceHandle *> MeshData::getBoundingFace(EdgeHandle *vh)
{
    return m_edgeAndBoundFaceMap[vh];
}

EdgeHandle* MeshData::findEdge(VertexHandle *vh1, VertexHandle *vh2)
{
    if(getBoundingVertex(vh1).contains(vh2)){
        for(auto edgeHandle: getBoundingEdge(vh1)){
            auto edge1 = edge(edgeHandle);
            if(edge1->cmp(vh1, vh2)){
                return edgeHandle;
            }
        }
    }
    return nullptr;
}

VertexHandle *MeshData::getOppoVertexHandle(FaceHandle *faceHandle, EdgeHandle *edgeHandle)
{
    auto f = face(faceHandle);
    auto e = edge(edgeHandle);
    for(int i = 0; i < 3; i++){
        auto vh = f->vh(i);
        if(e->vertexHandle(0) == vh){
            continue;
        }
        if(e->vertexHandle(1) == vh){
            continue;
        }
        return vh;
    }
    return nullptr;
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

void MeshData::init()
{
    m_pBoundingBox = new BoundingBoxAABB;
}

QList<VertexHandle *> MeshData::vertexHandleList() const
{
    return m_vertexHandleList;
}

void MeshData::setVertexHandleList(const QList<VertexHandle *> &newVertexHandleList)
{
    m_vertexHandleList = newVertexHandleList;
}

void MeshData::printTopo()
{
    qDebug() << "step 1!!" << m_vertexAndBoundFaceMap.size();
    qDebug() << "step 2!!" << m_vertexAndBoundVertexMap.size();
    qDebug() << "step 3!!" << m_vertexAndBoundEdgeMap.size();
    qDebug() << "step 4!!" << m_edgeAndBoundFaceMap.size();
    qDebug() << "step 5!!" << m_faceAndBoundEdgeMap.size();
}

QList<EdgeHandle *> MeshData::edgeHandleList() const
{
    return m_edgeHandleList;
}

void MeshData::replaceVertex(VertexHandle *vh, QVector3D newPos)
{
    vertex(vh)->setPos(newPos);
}

void MeshData::setFaceNum(int newFaceNum)
{
    m_faceNum = newFaceNum;
}

void MeshData::removeVertex(VertexHandle *vh)
{
    m_vertexMap.remove(vh);
    m_vertexHandleList.removeOne(vh);
    m_vertexAndBoundFaceMap.remove(vh);
}

void MeshData::removeEdge(EdgeHandle *eh)
{
    auto e = edge(eh);
    for(int i = 0; i < 2; i++){
        auto key = e->vertexHandle(i);
        m_vertexAndBoundEdgeMap[key].removeOne(eh);
    }
    m_vertexAndBoundVertexMap[e->vertexHandle(0)].removeOne(e->vertexHandle(1));
    m_vertexAndBoundVertexMap[e->vertexHandle(1)].removeOne(e->vertexHandle(0));
    m_edgeAndBoundFaceMap.remove(eh);
    m_edgeMap.remove(eh);
    m_edgeHandleList.removeOne(eh);
}

void MeshData::clear()
{
    for(auto f: m_faceHandleList){
        removeFace(f);
    }
    for(auto v: m_vertexHandleList){
        removeVertex(v);
    }
}

void MeshData::assign(MeshData* data)
{
    QList <VertexHandle*> oldVhs = data->m_vertexHandleList;
    QList <VertexHandle*> vhs;
    for(auto v: data->m_vertexHandleList){
        auto pos = data->vertex(v)->pos();
        vhs.append(addVertex(pos));
    }
    for(auto fh: data->m_faceHandleList){
        auto f = data->face(fh);
        auto index0 = oldVhs.indexOf(f->vh(0));
        auto index1 = oldVhs.indexOf(f->vh(1));
        auto index2 = oldVhs.indexOf(f->vh(2));
        addFace(vhs[index0], vhs[index1], vhs[index2]);
    }
}

QVector4D MeshData::normalColor() const
{
    return m_normalColor;
}

void MeshData::setNormalColor(const QVector4D &newNormalColor)
{
    m_normalColor = newNormalColor;
}

QVector4D MeshData::color(FaceHandle *fh)
{
    if(m_specialColor.contains(fh)){
        return m_specialColor[fh];
    }
    return m_normalColor;
}

void MeshData::removeFace(FaceHandle *fh)
{
    auto f = face(fh);
    for(int i = 0; i < 3; i++){
        auto key = f->vh(i);
        m_vertexAndBoundFaceMap[key].removeOne(fh);
    }
    for(auto edgeVh: m_faceAndBoundEdgeMap[fh]){
        if(m_edgeAndBoundFaceMap[edgeVh].size() == 1){ //边也要删除
            removeEdge(edgeVh);
        }else{
            m_edgeAndBoundFaceMap[edgeVh].removeOne(fh);
        }
    }
    m_faceAndBoundEdgeMap.remove(fh);
    m_faceMap.remove(fh);
    m_faceHandleList.removeOne(fh);
     m_faceNum--;
}

QMap<FaceHandle *, QVector4D> MeshData::specialColor() const
{
    return m_specialColor;
}

void MeshData::setSpecialColor(const QMap<FaceHandle *, QVector4D> &newSpecialColor)
{
    m_specialColor = newSpecialColor;
}

QList<FaceHandle *> MeshData::faceHandleList() const
{
    return m_faceHandleList;
}

void MeshData::updateAllColor(QVector4D color)
{

}

BoundingBox *MeshData::pBoundingBox() const
{
    return m_pBoundingBox;
}

void MeshData::setPBoundingBox(BoundingBox *newPBoundingBox)
{
    m_pBoundingBox = newPBoundingBox;
}
