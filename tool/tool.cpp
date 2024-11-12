#include "tool.h"
#include <QStringList>
#include <QRandomGenerator>
#include "datas/model.h"
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
    int acc = 35;
    float r = 7;
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
