#include "model.h"

Model::Model() {
    initializeOpenGLFunctions();
    init();
}

MeshData *Model::pMesh() const
{
    return m_pMesh;
}

void Model::setPMesh(MeshData *newPMesh)
{
    m_pMesh = newPMesh;
}

void Model::init()
{
    m_pMesh = new MeshData;
}

int Model::nodeMask() const
{
    return m_nodeMask;
}

void Model::setNodeMask(int newNodeMask)
{
    m_nodeMask = newNodeMask;
}

void Model::addChild(Model *child)
{
    m_children.append(child);
}

QList<Model *> Model::children() const
{
    return m_children;
}

void Model::setChildren(const QList<Model *> &newChildren)
{
    m_children = newChildren;
}

ShaderProgram *Model::pShader() const
{
    return m_pShader;
}

void Model::setPShader(ShaderProgram *newPShader)
{
    m_pShader = newPShader;
}

void Model::setMatrix(QMatrix4x4 mat)
{
    m_matrix = mat;
    if(m_pShader){
        m_pShader->setMatrix("model", mat);
    }
}

QMatrix4x4 Model::getMatrix()
{
    return m_matrix;
}

void Model::updateMeshToShader()
{
    if(!m_pShader){
        return;
    }
    m_pShader->use();
    glGenBuffers(1, &m_vbo);
    // float vertices[] = {
                        // 1, 0, 0, 0, 1, 0, -1, 0, 0, 0, 1, 0, 0, 0, 1, -1, 0, 0, 0, 0, 1, 1, 0, 0, -1, 0, 0
        // -0.5f, -0.5f, 0.0f,
        // 0.5f, -0.5f, 0.0f,
        // 0.0f,  0.5f, 0.0f,
        // 0.3f + -0.5f, -0.5f, 0.0f,
        // 0.3f + 0.5f, -0.5f, 0.0f,
        // 0.3f + 0.0f,  0.5f, 0.0f
    // };
    auto data = m_pMesh->getVertices();

    float* vertices = new float[data.size()];
    for (int i = 0; i < data.size(); ++i) {
        vertices[i] = data.at(i);
    }

    qDebug() << "chufa end" << vertices;
    glBindBuffer(GL_ARRAY_BUFFER, m_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), vertices, GL_STATIC_DRAW);
    m_pShader->use();
    // 0. 复制顶点数组到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), vertices, GL_STATIC_DRAW);
    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 2. 当我们渲染一个物体时要使用着色器程序
    // glUseProgram(shaderProgram);
    // 3. 绘制物体
    // 1. 绑定VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), vertices, GL_STATIC_DRAW);
    // 3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(m_vao);
}
