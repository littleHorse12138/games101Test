#ifndef LIGHT_H
#define LIGHT_H
#include <QVector3D>
class Light
{
public:
    Light();
    QVector3D lightPos() const;
    void setLightPos(const QVector3D &newLightPos);

    QVector3D lightColor() const;
    void setLightColor(const QVector3D &newLightColor);

private:
    QVector3D m_lightPos = QVector3D(10, 10, 10);
    QVector3D m_lightColor = QVector3D(1, 1, 1);
};

#endif // LIGHT_H
