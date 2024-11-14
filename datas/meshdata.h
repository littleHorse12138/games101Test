#ifndef MESHDATA_H
#define MESHDATA_H
#include "datas/face.h"
#include "datas/facehandle.h"
#include "vertex.h"
#include "datas/vertexhandle.h"
#include "datas/edge.h"
#include "datas/edgehandle.h"

#include <QList>
#include <QMap>
class Model;
class Material;
class BoundingBox;
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
    Edge* edge(EdgeHandle* handle);

    int faceNum() const;

    QList <float> getVertices();
    int vertexNum() const;

    //拓扑关系
    QList <FaceHandle*> getBoundingFace(VertexHandle* vh);
    QList <EdgeHandle*> getBoundingEdge(VertexHandle* vh);
    QList <VertexHandle*> getBoundingVertex(VertexHandle* vh);
    QList <FaceHandle*> getBoundingFace(EdgeHandle* vh);
    EdgeHandle* findEdge(VertexHandle* vh1, VertexHandle* vh2);
    VertexHandle *getOppoVertexHandle(FaceHandle *faceHandle, EdgeHandle *edgeHandle);
    //法向量
    QVector3D normal(VertexHandle* vh);
    QVector3D normal(FaceHandle* vh);
    Material *material() const;
    void setMaterial(Material *newMaterial);
    BoundingBox *pBoundingBox() const;
    void setPBoundingBox(BoundingBox *newPBoundingBox);

    QList<FaceHandle *> faceHandleList() const;

    void updateAllColor(QVector4D color);
    QMap<FaceHandle *, QVector4D> specialColor() const;
    void setSpecialColor(const QMap<FaceHandle *, QVector4D> &newSpecialColor);

    QVector4D normalColor() const;
    void setNormalColor(const QVector4D &newNormalColor);

    QVector4D color(FaceHandle* fh);

    void removeFace(FaceHandle* fh);
    void setFaceNum(int newFaceNum);

    void removeVertex(VertexHandle* vh);

    void clear();
    void assign(MeshData* data);

    QList<EdgeHandle *> edgeHandleList() const;

protected:
    void init();
private:
    Model* m_pPar = nullptr;

    QMap<FaceHandle*, Face*> m_faceMap;
    QList <FaceHandle*> m_faceHandleList;

    QMap<VertexHandle*, Vertex*> m_vertexMap;
    QList <VertexHandle*> m_vertexHandleList;

    QMap<EdgeHandle*, Edge*> m_edgeMap;
    QList <EdgeHandle*> m_edgeHandleList;

    int m_faceNum = 0;
    int m_vertexNum = 0;

    //相邻关系
    QMap <VertexHandle*, QList <FaceHandle*>> m_vertexAndBoundFaceMap;
    QMap <VertexHandle*, QList <VertexHandle*>> m_vertexAndBoundVertexMap;
    QMap <VertexHandle*, QList <EdgeHandle*>> m_vertexAndBoundEdgeMap;
    QMap <EdgeHandle*, QList <FaceHandle*>> m_edgeAndBoundFaceMap;
    QMap <FaceHandle*, QList <EdgeHandle*>> m_faceAndBoundEdgeMap;

    Material* m_material;
    BoundingBox* m_pBoundingBox = nullptr;

    QVector4D m_normalColor = QVector4D(1,0,0,1);
    QMap <FaceHandle*, QVector4D> m_specialColor;
};

#endif // MESHDATA_H
