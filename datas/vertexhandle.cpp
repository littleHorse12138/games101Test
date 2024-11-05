#include "vertexhandle.h"

VertexHandle::VertexHandle() {}

Vertex *VertexHandle::vertex() const
{
    return m_vertex;
}

void VertexHandle::setVertex(Vertex *newVertex)
{
    m_vertex = newVertex;
}
