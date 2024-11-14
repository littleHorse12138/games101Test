#include "tool.h"
#include <QStringList>
#include <QRandomGenerator>
#include "datas/model.h"
#include "canvas/openglwidget.h"
QString Tool::suffix(QString path)
{
    auto strList = path.split(".");
    return strList.empty()?"":strList.last();
}

float Tool::length(QPoint p)
{
    return sqrt(p.x()*p.x() + p.y()*p.y());
}

Model *GenerateModelTool::generateBall()
{
    Model* model = new Model;
    int acc = 10;
    float r = 0.1;
    QList <QList <VertexHandle*>> vhs;

    float vAngle;
    float hAngle;
    for(int i = 0; i < acc; i++){
        QList <VertexHandle*> vhs1;
        vAngle = -1*M_PI*0.5 + (M_PI * i / ((float)acc));
        for(int j = 0; j < acc; j++){
            hAngle = (2 * M_PI * j / ((float)acc));
            float h = r * sin(vAngle);
            float xy = r * cos(vAngle);
            float x = xy * cos(hAngle);
            float y = xy * sin(hAngle);
            QVector3D p(x, y, h);
            vhs1.append(model->pMesh()->addVertex(p));
        }
        vhs.append(vhs1);
    }

    int floorCnt = vhs.size();
    int oneCnt = vhs[0].size();
    for(int i = 0; i < floorCnt - 1; i++){
        for(int j = 0; j < oneCnt; j++){
            int n = j+1==oneCnt?0:j+1;
            model->pMesh()->addFace(vhs[i][j], vhs[i][n], vhs[i+1][n]);
            model->pMesh()->addFace(vhs[i][j], vhs[i+1][n], vhs[i+1][j]);
        }
    }
    return model;
}

int Tool::random(int low,int high)
{
    if(low > high){
        qSwap(low, high);
    }else if(low == high){
        return low;
    }else{
        int diff = high - low;
        auto random = QRandomGenerator::global()->bounded(diff);
        random += diff;
        return random;
    }
    return -1;
}

Model *GenerateModelTool::generateCube()
{
    Model* model = new Model;
    QList <VertexHandle*> vhs;
    vhs.append(model->pMesh()->addVertex(QVector3D(1,1,1)));
    vhs.append(model->pMesh()->addVertex(QVector3D(1,1,1)));
    vhs.append(model->pMesh()->addVertex(QVector3D(1,1,1)));
    vhs.append(model->pMesh()->addVertex(QVector3D(1,1,1)));
    vhs.append(model->pMesh()->addVertex(QVector3D(1,1,1)));
    vhs.append(model->pMesh()->addVertex(QVector3D(1,1,1)));
    vhs.append(model->pMesh()->addVertex(QVector3D(1,1,1)));
    return model;
}

LoopSubdivisionTool::LoopSubdivisionTool(Model *model)
{
    m_pModel = model;
}

void LoopSubdivisionTool::doLoop()
{
    auto mesh = m_pModel->pMesh();
    qDebug() << "doLoop!!@@" << mesh->edgeHandleList().size();
    QMap <EdgeHandle*, VertexHandle*> m_oldEdgeAndNewVertex;

    int cnt = 0;
    for(auto edgeVh: mesh->edgeHandleList()){
        if(mesh->getBoundingFace(edgeVh).size() == 2){
            auto e = mesh->edge(edgeVh);
            auto vh1 = e->vertexHandle(0);
            auto vh2 = e->vertexHandle(1);
            auto p0 = mesh->vertex(vh1)->pos();
            auto p1 = mesh->vertex(vh2)->pos();
            auto newPos = (p0 + p1) / 2.0;
            m_oldEdgeAndNewVertex.insert(edgeVh, mesh->addVertex(newPos));
        }else{
            auto e = mesh->edge(edgeVh);
            auto vLeft = mesh->vertex(e->vertexHandle(0));
            auto vRight = mesh->vertex(e->vertexHandle(1));
            auto boundingFaceList = mesh->getBoundingFace(edgeVh);
            auto vUp = mesh->vertex(mesh->getOppoVertexHandle(boundingFaceList[0], edgeVh));
            auto vLow = mesh->vertex(mesh->getOppoVertexHandle(boundingFaceList[1], edgeVh));
            auto newPos = vLeft->pos()*3.0/8.0 + vRight->pos()*3.0/8.0 + vUp->pos()/8.0 + vLow->pos()/8.0;
            m_oldEdgeAndNewVertex.insert(edgeVh, mesh->addVertex(newPos));
        }
    }

    auto oldFaceList = mesh->faceHandleList();
    QList <FaceHandle*> newFaceHandle;
    for(auto fh: oldFaceList){
        auto f = mesh->face(fh);
        auto v0 = f->vh(0);
        auto v2 = f->vh(1);
        auto v4 = f->vh(2);
        auto edge1 = mesh->findEdge(v0, v2);
        auto edge2 = mesh->findEdge(v2, v4);
        auto edge3 = mesh->findEdge(v4, v0);
        auto v1 = m_oldEdgeAndNewVertex[edge1];
        auto v3 = m_oldEdgeAndNewVertex[edge2];
        auto v5 = m_oldEdgeAndNewVertex[edge3];
        mesh->addFace(v0, v1, v5);
        mesh->addFace(v1, v2, v3);
        mesh->addFace(v5, v3, v4);
        mesh->addFace(v5, v1, v3);
    }
    for(auto face: oldFaceList){
        mesh->removeFace(face);
    }
    m_pModel->updateMeshToShader();
    return;
}
