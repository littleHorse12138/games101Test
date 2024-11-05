#include "tool.h"
#include <QStringList>
QString Tool::suffix(QString path)
{
    auto strList = path.split(".");
    return strList.empty()?"":strList.last();
}
