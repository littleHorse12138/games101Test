#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <QList>
#include <QPoint>
#include <QVector3D>
#include "datas/model.h"
#include "datas/viewer.h"
#include "datas/face.h"
namespace Intersection{
Model *isMouseIntersection(QList <Model*> np, QPointF mousePos, Viewer* viewer);
bool isIntersect(QVector3D start, QVector3D dir, QVector3D A, QVector3D B, QVector3D C, QVector3D &inter, QVector3D& normal);
}

#endif // INTERSECTION_H
