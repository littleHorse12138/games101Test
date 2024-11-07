#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QObject>
#include <QVector3D>
class MeshData;
class BoundingBox : public QObject
{
    Q_OBJECT
public:
    explicit BoundingBox(QObject *parent = nullptr);

    virtual void updateData(MeshData* data) = 0;
    virtual bool isIntersection(QVector3D start, QVector3D dir) = 0;
};

class BoundingBoxAABB: public BoundingBox
{
public:
    virtual void updateData(MeshData* data);
    virtual bool isIntersection(QVector3D start, QVector3D dir);
private:
    float m_maxX;
    float m_maxY;
    float m_maxZ;
    float m_minX;
    float m_minY;
    float m_minZ;
};

#endif // BOUNDINGBOX_H
