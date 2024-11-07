#include "boundingbox.h"
#include "datas/meshdata.h"
BoundingBox::BoundingBox(QObject *parent)
    : QObject{parent}
{}

void BoundingBoxAABB::updateData(MeshData *data)
{
    m_maxX = INT_MIN;
    m_maxY = INT_MIN;
    m_maxZ = INT_MIN;
    m_minX = INT_MAX;
    m_minY = INT_MAX;
    m_minZ = INT_MAX;
    for(int i = 0; i < data->vertexNum(); i++){
        auto handle = data->vertexHandle(i);
        auto v = data->vertex(handle);
        auto pos = v->pos();
        m_maxX = qMax(m_maxX, pos[0]);
        m_minX = qMin(m_minX, pos[0]);
        m_maxY = qMax(m_maxY, pos[0]);
        m_minY = qMin(m_minY, pos[0]);
        m_maxZ = qMax(m_maxZ, pos[0]);
        m_minZ = qMin(m_minZ, pos[0]);
    }
}

bool BoundingBoxAABB::isIntersection(QVector3D start, QVector3D dir)
{
    QVector3D invDir = QVector3D(
        dir.x() != 0 ? 1.0f / dir.x() : 0,
        dir.y() != 0 ? 1.0f / dir.y() : 0,
        dir.z() != 0 ? 1.0f / dir.z() : 0
        );

    // 计算与AABB六个面的交点参数t
    float t0 = (m_minX - start.x()) * invDir.x();
    float t1 = (m_maxX - start.x()) * invDir.x();
    float t2 = (m_minY - start.y()) * invDir.y();
    float t3 = (m_maxY - start.y()) * invDir.y();
    float t4 = (m_minZ - start.z()) * invDir.z();
    float t5 = (m_maxZ - start.z()) * invDir.z();

    // 找到进入和离开AABB的最小和最大t值
    float tMin = fmax(fmax(fmin(t0, t1), fmin(t2, t3)), fmin(t4, t5));
    float tMax = fmin(fmin(fmax(t0, t1), fmax(t2, t3)), fmax(t4, t5));

    // 如果tMax小于tMin，或者tMax小于0，则射线不与AABB相交
    return tMax >= tMin && tMax >= 0;
}
