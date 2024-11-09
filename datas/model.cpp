#include "model.h"
#include "datas/boundingbox.h"
#include "manager/materialmanager.h"
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
    MM->bindModelToStainlessSteelMaterial(this);
}

QString Model::name() const
{
    return m_name;
}

void Model::setName(const QString &newName)
{
    m_name = newName;
}

unsigned int Model::vao() const
{
    return m_vao;
}

void Model::setVao(unsigned int newVao)
{
    m_vao = newVao;
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
    m_pShader->use();
    auto data = pMesh()->getVertices();
    GLfloat* vertices = new GLfloat[data.size()];
    for(int i = 0; i < data.size(); i++){
        vertices[i] = data[i];
    }
    qDebug() << "update mesh" << sizeof(data);
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    m_vao = VAO;
    m_vbo = VBO;

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    pMesh()->pBoundingBox()->updateData(pMesh());
}
