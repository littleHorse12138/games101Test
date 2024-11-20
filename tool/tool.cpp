#include "tool.h"
#include <QStringList>
#include <QRandomGenerator>
#include "datas/model.h"
#include "canvas/openglwidget.h"
#include "QElapsedTimer"
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
    int acc = 6;
    float r = 10;
    QList <QList <VertexHandle*>> vhs;

    float vAngle;
    float hAngle;
    for(int i = 1; i < acc; i++){
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

    auto head = model->pMesh()->addVertex(QVector3D(0, 0, -r));
    auto tail = model->pMesh()->addVertex(QVector3D(0, 0, r));
    for(int j = 0; j < oneCnt; j++){
        int n = j+1==oneCnt?0:j+1;
        model->pMesh()->addFace(vhs[0][j], vhs[0][n], head);
        model->pMesh()->addFace(tail, vhs[floorCnt-1][j], vhs[floorCnt-1][n]);
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
    float l = 2;
    vhs.append(model->pMesh()->addVertex(QVector3D(l,l,l)));
    vhs.append(model->pMesh()->addVertex(QVector3D(l,-l,l)));
    vhs.append(model->pMesh()->addVertex(QVector3D(l,-l,-l)));
    vhs.append(model->pMesh()->addVertex(QVector3D(l,l,-l)));
    vhs.append(model->pMesh()->addVertex(QVector3D(-l,l,l)));
    vhs.append(model->pMesh()->addVertex(QVector3D(-l,-l,l)));
    vhs.append(model->pMesh()->addVertex(QVector3D(-l,-l,-l)));
    vhs.append(model->pMesh()->addVertex(QVector3D(-l,l,-l)));
    model->pMesh()->addFace(vhs[0], vhs[1], vhs[2]);
    model->pMesh()->addFace(vhs[0], vhs[2], vhs[3]);

    model->pMesh()->addFace(vhs[6], vhs[5], vhs[4]);
    model->pMesh()->addFace(vhs[6], vhs[4], vhs[7]);

    model->pMesh()->addFace(vhs[4], vhs[0], vhs[3]);
    model->pMesh()->addFace(vhs[4], vhs[3], vhs[7]);

    model->pMesh()->addFace(vhs[1], vhs[5], vhs[2]);
    model->pMesh()->addFace(vhs[2], vhs[5], vhs[6]);

    model->pMesh()->addFace(vhs[5], vhs[1], vhs[0]);
    model->pMesh()->addFace(vhs[5], vhs[0], vhs[4]);

    model->pMesh()->addFace(vhs[3], vhs[6], vhs[2]);
    model->pMesh()->addFace(vhs[3], vhs[7], vhs[6]);
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

    QElapsedTimer timer;
    timer.start();
    QList <VertexHandle*> oldVhs = mesh->vertexHandleList();
    QList <VertexHandle*> newVhs;
    for(auto edgeVh: mesh->edgeHandleList()){
        auto e = mesh->edge(edgeVh);
        auto vh1 = e->vertexHandle(0);
        auto vh2 = e->vertexHandle(1);
        auto p0 = mesh->vertex(vh1)->pos();
        auto p1 = mesh->vertex(vh2)->pos();
        auto newPos = (p0 + p1) / 2.0;
        auto vhNew = mesh->addVertex(newPos);
        m_oldEdgeAndNewVertex.insert(edgeVh, vhNew);
        newVhs.append(vhNew);
    }

    qDebug() << "步骤1 生成新顶点结束" << timer.elapsed();
    auto oldFaceList = mesh->faceHandleList();
    QList <FaceHandle*> newFaceHandle;
    QMap <VertexHandle*, QList <VertexHandle*>> newVAndBoundV;
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
        newVAndBoundV[v1].append(v0);
        newVAndBoundV[v1].append(v2);
        newVAndBoundV[v1].append(v3);
        newVAndBoundV[v1].append(v5);
        newVAndBoundV[v3].append(v1);
        newVAndBoundV[v3].append(v2);
        newVAndBoundV[v3].append(v4);
        newVAndBoundV[v3].append(v5);
        newVAndBoundV[v5].append(v0);
        newVAndBoundV[v5].append(v1);
        newVAndBoundV[v5].append(v3);
        newVAndBoundV[v5].append(v4);
    }
    qDebug() << "步骤2 生成新面结束" << timer.elapsed();
    for(auto face: oldFaceList){
        mesh->removeFace(face);
    }
    qDebug() << "步骤3 删除旧面结束" << timer.elapsed();

    QMap <VertexHandle*, QVector3D> vertexAndNewPos;
    for(auto vh: mesh->vertexHandleList()){
        if(oldVhs.contains(vh)){
            auto v = mesh->vertex(vh);
            if(mesh->getBoundingEdge(vh).size() != mesh->getBoundingVertex(vh).size()){
                qDebug() << "eror occ";
            }
            float n = mesh->getBoundingEdge(vh).size();
            float u = mesh->getBoundingEdge(vh).size()==3?(3.0 / 16.0):(3/(8.0*n));
            QVector3D newPos = v->pos() * (1 - n*u);
            QVector3D otherSum(0,0,0);
            for(auto vh1: mesh->getBoundingVertex(vh)){
                otherSum += mesh->vertex(vh1)->pos();
            }
            newPos += u * otherSum;
            vertexAndNewPos.insert(vh, newPos);
        }else{
            if(newVAndBoundV[vh].size() == 8){
                QVector3D newPos1(0,0,0);
                for(auto vh1: newVAndBoundV[vh]){
                    newPos1 += mesh->vertex(vh1)->pos() / 8.0;
                }
                vertexAndNewPos.insert(vh, newPos1);
            }else if(newVAndBoundV.size() == 4){

            }else{
                qDebug() << "error occu!" << newVAndBoundV[vh].size();
            }
        }
    }

    // for(auto edgeVh: m_oldEdgeAndNewVertex.keys()){
    //     auto vh = m_oldEdgeAndNewVertex[edgeVh];
    //     if(newVAndBoundV.size() == 1){
    //         auto e = mesh->edge(edgeVh);
    //         auto vh1 = e->vertexHandle(0);
    //         auto vh2 = e->vertexHandle(1);
    //         auto p0 = mesh->vertex(vh1)->pos();
    //         auto p1 = mesh->vertex(vh2)->pos();
    //         auto newPos = (p0 + p1) / 2.0;
    //         vertexAndNewPos.insert(vh, newPos);
    //     }else if(mesh->getBoundingFace(edgeVh).size() == 2){
    //         auto e = mesh->edge(edgeVh);
    //         auto vLeft = mesh->vertex(e->vertexHandle(0));
    //         auto vRight = mesh->vertex(e->vertexHandle(1));
    //         auto boundingFaceList = mesh->getBoundingFace(edgeVh);
    //         auto vUp = mesh->vertex(mesh->getOppoVertexHandle(boundingFaceList[0], edgeVh));
    //         auto vLow = mesh->vertex(mesh->getOppoVertexHandle(boundingFaceList[1], edgeVh));
    //         auto newPos = vLeft->pos()*3.0/8.0 + vRight->pos()*3.0/8.0 + vUp->pos()/8.0 + vLow->pos()/8.0;
    //         vertexAndNewPos.insert(vh, newPos);
    //     }else{

    //         qDebug() << "检测到非流形边！！" << mesh->getBoundingFace(edgeVh).size();
    //     }
    // }
    for(auto key: vertexAndNewPos.keys()){
        mesh->replaceVertex(key, vertexAndNewPos[key]);
    }

    qDebug() << "步骤4 替换旧顶点结束" << timer.elapsed();
    m_pModel->updateMeshToShader();
    qDebug() << "步骤5 更新到着色器结束" << timer.elapsed();
    return;
}
