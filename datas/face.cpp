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
