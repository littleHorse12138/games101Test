#include "intersection.h"
#include "datas/model.h"
#include "datas/viewer.h"
#include "datas/camera.h"
#include "datas/boundingbox.h"
#include "canvas/openglwidget.h"

Model *Intersection::isMouseIntersection(QList<Model *> np, QPointF mousePos, Viewer *viewer, QVector3D& inter)
{
    auto camera = viewer->pCamera();

    auto startPoint = camera->cameraPos();
    QVector3D dir;

    //找到dir
    auto wgt = viewer->pParWgt();
    float w = (float)wgt->width();
    float h = (float)wgt->height();
    float x = mousePos.x() / w;
    float y = mousePos.y() / h;
    y = 1 - y;
    x = (x * 2) - 1;
    y = (y * 2) - 1;


    auto vp = camera->getPerspectiveMatrix() * camera->getViewMatrix();
    auto MVPInverse = vp.inverted();
    // 假设你已经有了MVP矩阵的逆矩阵：MVPInverse
    QVector4D rayNDC(x, y, 1.0, 1.0); // NDC坐标
    QVector4D rayClip = MVPInverse * rayNDC; // 转换到裁剪空间
    rayClip = rayClip / rayClip.w(); // 归一化

    // 射线方向
    QVector3D rayDir = QVector3D(rayClip) - camera->cameraPos(); // 从原点到射线方向

    // 射线起点
    QVector4D rayOrigin = MVPInverse * QVector4D(x, y, -1.0, 1.0); // 从NDC到世界空间
    rayOrigin = rayOrigin / rayOrigin.w(); // 归一化

    startPoint = QVector3D(rayOrigin);
    dir = rayDir;

    float minDis = 1000000;
    Model* minModel = nullptr;
    for(auto model: np){
        if(!model || !model->pShader() || !model->nodeMask()
            /*|| !model->pMesh()->pBoundingBox()->isIntersection(startPoint, dir)*/){
            continue;
        }
        for(auto fh: model->pMesh()->faceHandleList()){
            auto f = model->pMesh()->face(fh);
            QVector3D p[3];
            for(int i = 0; i < 3; i++){
                auto vh = f->vh(i);
                auto v = model->pMesh()->vertex(vh);
                p[i] = v->pos();
            }
            QVector3D normal;
            QVector3D nowInter;
            if(Intersection::isIntersect(startPoint, dir, p[0], p[1], p[2], nowInter, normal)){
                auto nowDis = (nowInter - viewer->pCamera()->cameraPos()).length();
                if(nowDis < minDis){
                    minDis = nowDis;
                    inter = nowInter;
                    minModel = model;
                }
            }
        }
        return minModel;
    }

    return nullptr;
}

bool Intersection::isIntersect(QVector3D start, QVector3D dir, QVector3D A, QVector3D B, QVector3D C, QVector3D &inter, QVector3D &normal)
{
    QVector3D edge1 = B - A;
    QVector3D edge2 = C - A;
    QVector3D h = dir.crossProduct(dir, edge2);
    float a = edge1.dotProduct(edge1, h);

    if (fabs(a) < std::numeric_limits<float>::epsilon()) {
        return false; // 射线与三角形平行或三角形面积为零
    }

    QVector3D s = start - A;
    float f = 1.0f / a;
    float u = f * s.dotProduct(s, h);

    if (u < 0.0f || u > 1.0f) {
        return false; // 交点在三角形外部
    }

    QVector3D q = s.crossProduct(s, edge1);
    float v = f * dir.dotProduct(dir, q);

    if (v < 0.0f || u + v > 1.0f) {
        return false; // 交点在三角形外部
    }

    float t = f * edge2.dotProduct(edge2, q);

    if (t > std::numeric_limits<float>::epsilon()) { // 交点在射线前方
        inter = start + dir * t; // 计算交点
        normal = edge1.crossProduct(edge1, edge2).normalized(); // 计算法向量
        return true;
    }

    return false; // 交点在射线后方
}
