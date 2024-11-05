#include "vertex.h"

Vertex::Vertex(QVector3D pos)
{
    m_pos = pos;
}

QVector3D Vertex::pos() const
{
    return m_pos;
}

void Vertex::setPos(const QVector3D &newPos)
{
    m_pos = newPos;
}
