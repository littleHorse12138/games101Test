#include "openglwidget.h"
#include "manager/shaderprogrammanager.h"
#include "datas/model.h"
#include "manager/meshdatamanager.h"
#include <QVector4D>
#include "manager/materialmanager.h"
#include "datas/light.h"
#include <QWheelEvent>
OpenglWidget::OpenglWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    init();
}

OpenglWidget *OpenglWidget::getInstance()
{
    static OpenglWidget* instance = nullptr;
    if(!instance){
        instance = new OpenglWidget;
    }
    return instance;
}

void OpenglWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void OpenglWidget::resizeGL(int w, int h)
{
    m_pCamera->widgetScaleChanged(w, h);
}

void OpenglWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawModel(MDM->root());
}

void OpenglWidget::showEvent(QShowEvent *ev)
{
    testInit();
}

void OpenglWidget::mousePressEvent(QMouseEvent *ev)
{

}

void OpenglWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton){
        qDebug() << "chufa!";
    }
}

void OpenglWidget::mouseReleaseEvent(QMouseEvent *ev)
{

}

void OpenglWidget::wheelEvent(QWheelEvent *ev)
{
    if(ev->angleDelta().y() > 0){
        m_pCamera->moveFront();
    }else{
        m_pCamera->moveBack();
    }
    update();
}

void OpenglWidget::drawModel(Model *model)
{
    if(!model){
        return;
    }
    if(model->pMesh() && model->pShader() && model->nodeMask()){
        qDebug() << "drawModel!!";
        model->pShader()->use();
        glDrawArrays(GL_TRIANGLES, 0, model->pMesh()->faceNum() * 3);
        model->pShader()->unUse();
    }
    for(auto child: model->children()){
        drawModel(child);
    }
}

void OpenglWidget::init()
{
    m_pCamera = new Camera;
}

void OpenglWidget::testInit()
{
    Model* newModel = new Model;
    MDM->readMesh(newModel->pMesh(), "C:/test1/test.obj");
    SM->bindToBlingPhoneShader(newModel, m_pCamera);
    newModel->updateMeshToShader();
    MDM->addModel(newModel);
    update();


    QMatrix4x4 mat1;
    newModel->setMatrix(mat1);
    newModel->pShader()->setMatrix("projection", m_pCamera->getPerspectiveMatrix());
    newModel->pShader()->setMatrix("view", m_pCamera->getViewMatrix());

    MM->bindModelToRubberMaterial(newModel);

    m_pLight = new Light;

    newModel->pShader()->setVec3("lightColor", m_pLight->lightColor());
    newModel->pShader()->setVec3("lightPos", m_pLight->lightPos());
    newModel->pShader()->setVec3("viewPos", m_pCamera->cameraPos());


}

Camera *OpenglWidget::pCamera() const
{
    return m_pCamera;
}

void OpenglWidget::setPCamera(Camera *newPCamera)
{
    m_pCamera = newPCamera;
}
