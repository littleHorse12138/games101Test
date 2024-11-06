#include "tool.h"
#include <QStringList>
QString Tool::suffix(QString path)
{
    auto strList = path.split(".");
    return strList.empty()?"":strList.last();
}

float Tool::length(QPoint p)
{
    return sqrt(p.x()*p.x() + p.y()*p.y());
}
