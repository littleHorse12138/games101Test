#include "edge.h"
#include "datas/vertexhandle.h"
Edge::Edge(VertexHandle *vh1, VertexHandle *vh2)
{
    m_pVh[0] = vh1;
    m_pVh[1] = vh2;
}

bool Edge::cmp(VertexHandle *vh1, VertexHandle *vh2)
{
    if(vh1 == m_pVh[0] && vh2 == m_pVh[1]){
        return true;
    }
    if(vh1 == m_pVh[1] && vh2 == m_pVh[0]){
        return true;
    }
    return false;
}

VertexHandle *Edge::vertexHandle(int index)
{
    return m_pVh[index];
}
