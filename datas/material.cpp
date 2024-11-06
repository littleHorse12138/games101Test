#include "material.h"
#include <QDebug>
Material::Material() {}

QVector3D Material::diffuse() const
{
    return m_diffuse;
}

void Material::setDiffuse(const QVector3D &newDiffuse)
{
    m_diffuse = newDiffuse;
}

QVector3D Material::specular() const
{
    return m_specular;
}

void Material::setSpecular(const QVector3D &newSpecular)
{
    m_specular = newSpecular;
}



float Material::shininess() const
{
    return m_shininess;
}

void Material::setShininess(float newShininess)
{
    m_shininess = newShininess;
}

QVector3D Material::ambient() const
{
    return m_ambient;
}

void Material::setAmbient(const QVector3D &newAmbient)
{
    m_ambient = newAmbient;
}


MaterialRubber::MaterialRubber()
{
    init();
}

void MaterialRubber::init()
{
    setDiffuse(QVector3D(0.2f, 0.2f, 0.2f));
    setSpecular(QVector3D(0.3f, 0.3f, 0.3f));
    setAmbient(QVector3D(0.1f, 0.1f, 0.1f));
    setShininess(10.0f);
}

MaterialStainlessSteel::MaterialStainlessSteel()
{
    init();
}

void MaterialStainlessSteel::init()
{
    setDiffuse(QVector3D(0.6f, 0.6f, 0.6f));
    setSpecular(QVector3D(1.0f, 1.0f, 1.0f));
    setAmbient(QVector3D(0.3f, 0.3f, 0.3f));
    setShininess(64);
}
