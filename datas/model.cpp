#include "model.h"
#include "datas/boundingbox.h"
#include "manager/materialmanager.h"
#include "canvas/openglwidget.h"
#include "manager/shaderprogrammanager.h"
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

Model *Model::pBBModel() const
{
    return m_pBBModel;
}

void Model::setPBBModel(Model *newPBBModel)
{
    m_pBBModel = newPBBModel;
}

Model *Model::pPolygonModel() const
{
    return m_pPolygonModel;
}

void Model::setPPolygonModel(Model *newPPolygonModel)
{
    m_pPolygonModel = newPPolygonModel;
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

bool Model::bIsLineModel() const
{
    return m_bIsLineModel;
}

void Model::setBIsLineModel(bool newBIsLineModel)
{
    if(newBIsLineModel && m_pBBModel){
        removeChild(m_pBBModel);
        removeChild(m_pPolygonModel);
        // m_pBBModel = nullptr;

        // m_pPolygonModel = nullptr;
        // m_pPolygonModel->setBIsLineModel(true);
        // addChild(m_pPolygonModel);
    }
    m_bIsLineModel = newBIsLineModel;
}

void Model::initBBModelAndPolygonModel()
{
    if(m_pBBModel){
        return;
    }
    m_pBBModel = new Model;

    m_pPolygonModel = new Model;
    m_pPolygonModel->setBIsLineModel(true);
    m_pPolygonModel->pMesh()->setNormalColor(QVector4D(0,0,0,1));
    addChild(m_pPolygonModel);
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

bool Model::removeChild(Model *child)
{
    return m_children.removeOne(child);
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
    if(m_pPolygonModel){
        QMatrix4x4 matScale;
        matScale.scale(QVector3D(1, 1, 1));
        m_pPolygonModel->setMatrix(matScale * mat);
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

        OW->glGenBuffers(1, &VBO);

        m_vao = VAO;
        m_vbo = VBO;
    }else{
        VAO = m_vao;
        VBO = m_vbo;

    }

    OW->glBindVertexArray(VAO);

    OW->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    OW->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), vertices, GL_STATIC_DRAW);
    OW->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(0 * sizeof(float)));
    OW->glEnableVertexAttribArray(0);

    OW->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    OW->glEnableVertexAttribArray(1);

    OW->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    OW->glEnableVertexAttribArray(2);

    if(m_pPolygonModel){
        m_pPolygonModel->pMesh()->assign(pMesh());
        m_pPolygonModel->updateMeshToShader();
    }


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

}
