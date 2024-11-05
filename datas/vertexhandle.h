#ifndef VERTEXHANDLE_H
#define VERTEXHANDLE_H
#include "datas/vertex.h"
class VertexHandle
{
public:
    VertexHandle();
    Vertex *vertex() const;
    void setVertex(Vertex *newVertex);

private:
    Vertex* m_vertex = nullptr;
};

#endif // VERTEXHANDLE_H
