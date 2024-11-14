#ifndef EDGE_H
#define EDGE_H
class VertexHandle;
class Edge
{
public:
    Edge(VertexHandle* vh1, VertexHandle* vh2);
    bool cmp(VertexHandle* vh1, VertexHandle* vh2);
    VertexHandle* vertexHandle(int index);
private:
    VertexHandle* m_pVh[2];
};

#endif // EDGE_H
