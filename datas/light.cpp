#include "light.h"

Light::Light() {}

QVector3D Light::lightPos() const
{
    return m_lightPos;
}

void Light::setLightPos(const QVector3D &newLightPos)
{
    m_lightPos = newLightPos;
    emit sgLightChanged();
}

QVector3D Light::lightColor() const
{
    return m_lightColor;
}

void Light::setLightColor(const QVector3D &newLightColor)
{
    emit sgLightChanged();
    m_lightColor = newLightColor;
}
