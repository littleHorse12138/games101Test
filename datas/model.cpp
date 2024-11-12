#include "model.h"
#include "datas/boundingbox.h"
#include "manager/materialmanager.h"
#include "canvas/openglwidget.h"
Model::Model() {
    // initializeOpenGLFunctions();
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

void Model::useVAO()
{
    OW->glBindVertexArray(m_vao);
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
    m_children.prepend(child);
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

void Model::updateMeshToShader(int x)
{
    m_pShader->use();
    auto data = pMesh()->getVertices();
    GLfloat* vertices = new GLfloat[data.size()];
    for(int i = 0; i < data.size(); i++){
        vertices[i] = data[i];
    }
    GLuint VAO = 1000000;
    GLuint VBO = 1000000;
    // int x = 1;
    if(m_vao == 1000000){
        OW->glGenVertexArrays(1, &VAO);
        qDebug() << "updateMesh1" << OW->glGetError();

        OW->glGenBuffers(1, &VBO);
        qDebug() << "updateMesh2" << OW->glGetError();

        m_vao = VAO;
        m_vbo = VBO;
    }else{
        qDebug() << "use old";
        VAO = m_vao;
        VBO = m_vbo;

    }

    OW->glBindVertexArray(VAO);

    OW->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    OW->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), vertices, GL_STATIC_DRAW);
    qDebug() << "updateMesh4" << OW->glGetError();

    OW->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(0 * sizeof(float)));
    OW->glEnableVertexAttribArray(0);

    OW->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    OW->glEnableVertexAttribArray(1);

    OW->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    OW->glEnableVertexAttribArray(2);
    qDebug() << "updateMesh5" << OW->glGetError();

    // OW->glBindBuffer(GL_ARRAY_BUFFER, 0);
    // OW->glBindVertexArray(0);
}

void Model::updateMeshToShader2(int x)
{
    m_pShader->use();
    GLuint VAO = 1000000;
    GLuint VBO = 1000000;

    VAO = m_vao;
    VBO = m_vbo;

    OW->glBindVertexArray(VAO);
    OW->glBindBuffer(GL_ARRAY_BUFFER, VBO);

    OW->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(0 * sizeof(float)));
    OW->glEnableVertexAttribArray(0);

    OW->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    OW->glEnableVertexAttribArray(1);

    OW->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    OW->glEnableVertexAttribArray(2);
    qDebug() << "updateMesh5" << OW->glGetError();

}
