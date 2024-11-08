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

}

namespace GenerateModelTool{
Model* generateBall(float radius);
}
#endif // TOOL_H
