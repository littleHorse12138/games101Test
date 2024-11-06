#ifndef MATERIAL_H
#define MATERIAL_H
#include <QVector3D>
class Material
{
public:
    enum Type{
        Rubber = 0,
    };
    Material();
    QVector3D diffuse() const;
    void setDiffuse(const QVector3D &newDiffuse);

    QVector3D specular() const;
    void setSpecular(const QVector3D &newSpecular);

    float shininess() const;
    void setShininess(float newShininess);

    QVector3D ambient() const;
    void setAmbient(const QVector3D &newAmbient);

private:
    QVector3D m_diffuse;
    QVector3D m_specular;
    QVector3D m_ambient;
    float m_shininess;
};

class MaterialRubber: public Material
{
public:
    MaterialRubber();
protected:
    void init();
};

class MaterialStainlessSteel: public Material
{
public:
    MaterialStainlessSteel();
protected:
    void init();
};

#endif // MATERIAL_H
