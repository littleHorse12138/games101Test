#ifndef FACE_H
#define FACE_H
#include "datas/vertexhandle.h"
class Face
{
public:
    Face();
    Face(VertexHandle* vh1, VertexHandle* vh2, VertexHandle* vh3);
    VertexHandle* vh(int index);
private:
    VertexHandle* m_pVhs[3];
};

#endif // FACE_H
