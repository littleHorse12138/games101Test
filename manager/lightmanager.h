#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <QObject>

class LightManager : public QObject
{
    Q_OBJECT
public:
    explicit LightManager(QObject *parent = nullptr);

signals:
};

#endif // LIGHTMANAGER_H
