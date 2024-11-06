#ifndef VERTEX_H
#define VERTEX_H
#include <QVector3D>
class VertexHandle;
class Vertex
{
public:
    Vertex(QVector3D pos = QVector3D(0,0,0));
    QVector3D pos() const;
    void setPos(const QVector3D &newPos);
private:
    QVector3D m_pos;
};

#endif // VERTEX_H
