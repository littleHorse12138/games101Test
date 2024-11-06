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
    glEnable(GL_DEPTH_TEST);
}

void OpenglWidget::resizeGL(int w, int h)
{
    m_pCamera->widgetScaleChanged(w, h);
}

void OpenglWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawModel(MDM->root());
    m_updateTimeSinceLastUpdate++;
}

void OpenglWidget::showEvent(QShowEvent *ev)
{
    testInit();
}

void OpenglWidget::mousePressEvent(QMouseEvent *ev)
{
    m_lastMousePlace = ev->pos();
}

void OpenglWidget::mouseMoveEvent(QMouseEvent *ev)
{
    auto nowPlace = ev->pos();

    if(ev->buttons() == Qt::LeftButton){
        qDebug() << "chufa!";
    }else if(ev->buttons() == Qt::MiddleButton){
        m_pCamera->moveTranslate(nowPlace - m_lastMousePlace);
    }else if(ev->buttons() == Qt::RightButton){
        m_pCamera->moveRotate(nowPlace - m_lastMousePlace);
    }

    m_lastMousePlace = nowPlace;
    update();
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
        model->pShader()->use();
        glBindVertexArray(model->vao());
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

    m_pUpdateTimer = new QTimer;
    connect(m_pUpdateTimer, &QTimer::timeout, this, &OpenglWidget::onTimerUpdateTimeout);
    m_pUpdateTimer->start(1);

     m_pFpsWidget = new FpsWidget(this, this);
     m_pFpsWidget->resize(200, 50);
    m_pFpsWidget->move(0,0);

     resize(800, 600);
}

void OpenglWidget::testInit()
{
    Model* newModel = new Model;
    MDM->readMesh(newModel->pMesh(), "C:/test1/test.obj");
    SM->bindToBlingPhoneShader(newModel, m_pCamera);
    newModel->pShader()->use();
    newModel->updateMeshToShader();
    newModel->pShader()->use();
    MDM->addModel(newModel);
    update();



    MM->bindModelToRubberMaterial(newModel);

    m_pLight = new Light;

    newModel->pShader()->setVec3("lightColor", m_pLight->lightColor());
    newModel->pShader()->setVec3("lightPos", m_pLight->lightPos());
    newModel->pShader()->setVec3("viewPos", m_pCamera->cameraPos());


    QMatrix4x4 mat1;
    newModel->setMatrix(mat1);
    newModel->pShader()->setMatrix("projection", m_pCamera->getPerspectiveMatrix());
    newModel->pShader()->setMatrix("view", m_pCamera->getViewMatrix());
    newModel->pShader()->unUse();

}

void OpenglWidget::onTimerUpdateTimeout()
{
    update();
}

void OpenglWidget::setUpdateTimeSinceLastUpdate(int newUpdateTimeSinceLastUpdate)
{
    m_updateTimeSinceLastUpdate = newUpdateTimeSinceLastUpdate;
}

int OpenglWidget::updateTimeSinceLastUpdate() const
{
    return m_updateTimeSinceLastUpdate;
}

Camera *OpenglWidget::pCamera() const
{
    return m_pCamera;
}

void OpenglWidget::setPCamera(Camera *newPCamera)
{
    m_pCamera = newPCamera;
}
