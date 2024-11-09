#include "face.h"

Face::Face() {}

Face::Face(VertexHandle *vh1, VertexHandle *vh2, VertexHandle *vh3)
{
    m_pVhs[0] = vh1;
    m_pVhs[1] = vh2;
    m_pVhs[2] = vh3;
}

VertexHandle *Face::vh(int index)
{
    return m_pVhs[index];
}

QVector3D Face::normal()
{
    auto p1 = m_pVhs[0]->vertex()->pos();
    auto p2 = m_pVhs[1]->vertex()->pos();
    auto p3 = m_pVhs[2]->vertex()->pos();
    auto dir1 = p2 - p1;
    auto dir2 = p3 - p1;
    dir1.normalize();
    dir2.normalize();
    return dir1.crossProduct(dir1, dir2);
}

float Face::area()
{
    auto p1 = m_pVhs[0]->vertex()->pos();
    auto p2 = m_pVhs[1]->vertex()->pos();
    auto p3 = m_pVhs[2]->vertex()->pos();
    float a = (p1-p2).length();
    float b = (p1-p3).length();
    float c = (p2-p3).length();
    float s = a + b + c;
    float area = sqrt(s * (s-a) * (s-b) * (s-c));
    return area;
}

