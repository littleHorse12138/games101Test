#ifndef TOOL_H
#define TOOL_H

#include <QString>
#include <QPoint>
#include "datas/model.h"
#include "datas/camera.h"
#include "datas/viewer.h"
namespace Tool{
QString suffix(QString path); //获取后缀名；
float length(QPoint p);
int random(int low, int high);
}

namespace GenerateModelTool{
Model* generateBall();
Model* generateCube();
Model* generateCylinder();
}

class LoopSubdivisionTool{
public:
    LoopSubdivisionTool(Model* model);
    void doLoop();
private:
    Model* m_pModel = nullptr;
};

#endif // TOOL_H
