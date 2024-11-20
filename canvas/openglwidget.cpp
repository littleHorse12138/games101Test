#include "openglwidget.h"
#include "manager/shaderprogrammanager.h"
#include "datas/model.h"
#include "manager/meshdatamanager.h"
#include <QVector4D>
#include "manager/materialmanager.h"
#include "datas/light.h"
#include <QWheelEvent>
#include "datas/viewer.h"
#include "tool/intersection.h"
#include "tool/tool.h"
#include "canvas/modeltreewgt.h"
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
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(3.0f);
}

void OpenglWidget::resizeGL(int w, int h)
{
    m_pViewer->pCamera()->widgetScaleChanged(w, h);
}

void OpenglWidget::paintGL()
{
    // qDebug() << "doPaint";
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
    if(ev->buttons() == Qt::LeftButton){
        QList <Model*> np;
        np.push_back(MDM->root()->children()[0]);
        QVector3D inter;
        if(Intersection::isMouseIntersection(np, ev->pos(), m_pViewer, inter)){
            qDebug() << "拾取到了" << inter;
            auto model = buildNewModel();
            QMatrix4x4 mat;
            mat.translate(inter);
            model->setMatrix(mat);
        }else{
            qDebug() << "没拾取";
        }
    }
    update();
}

void OpenglWidget::mouseMoveEvent(QMouseEvent *ev)
{
    auto nowPlace = ev->pos();

    if(ev->buttons() == Qt::LeftButton){

    }else if(ev->buttons() == Qt::MiddleButton){
        m_pViewer->pCamera()->moveTranslate(nowPlace - m_lastMousePlace);
    }else if(ev->buttons() == Qt::RightButton){
        m_pViewer->pCamera()->moveRotate(nowPlace - m_lastMousePlace);
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
        m_pViewer->pCamera()->moveFront();
    }else{
        m_pViewer->pCamera()->moveBack();
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
        model->updateMeshToShader2();
        if(model->bIsLineModel()){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glDrawArrays(GL_TRIANGLES, 0, model->pMesh()->faceNum() * 3);
        glBindVertexArray(0);
        model->pShader()->unUse();
    }
    for(auto child: model->children()){
        drawModel(child);
    }
}

void OpenglWidget::init()
{
    m_pViewer = new Viewer(this);

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
    {
        Model* newModel = GenerateModelTool::generateCube();
        // Model* newModel = new Model;
        newModel->initBBModelAndPolygonModel();
        // MDM->readMesh(newModel->pMesh(), "C:/test1/test.obj");
        SM->bindToBlingPhoneShader(newModel, m_pViewer);
        newModel->pMesh()->setNormalColor(QVector4D(0,1,0,1));
        newModel->updateMeshToShader();
        m_pViewer->updateAllDataToShader(newModel);
        MDM->addModel(newModel);
        QMatrix4x4 mat;
        mat.scale(10,10,10);
        // newModel->setMatrix(mat);
        newModel->setName("杯子");
        newModel->initBBModelAndPolygonModel();
        m_pModelTreeWgt->addModel(newModel);
    }
}

Model* OpenglWidget::buildNewModel()
{
    glUseProgram(0);
    Model* newModel = GenerateModelTool::generateBall();
    SM->bindToBlingPhoneShader(newModel, m_pViewer);
    newModel->pShader()->use();
    newModel->updateMeshToShader();
    m_pViewer->updateAllDataToShader(newModel);
    newModel->pMesh()->setNormalColor(QVector4D(0,0,1,1));
    MDM->addModel(newModel);
    return newModel;
}

void OpenglWidget::onTimerUpdateTimeout()
{
    update();
}

Viewer *OpenglWidget::pViewer() const
{
    return m_pViewer;
}

void OpenglWidget::setPViewer(Viewer *newPViewer)
{
    m_pViewer = newPViewer;
}

ModelTreeWgt *OpenglWidget::pModelTreeWgt() const
{
    return m_pModelTreeWgt;
}

void OpenglWidget::setPModelTreeWgt(ModelTreeWgt *newPModelTreeWgt)
{
    m_pModelTreeWgt = newPModelTreeWgt;
}

void OpenglWidget::setUpdateTimeSinceLastUpdate(int newUpdateTimeSinceLastUpdate)
{
    m_updateTimeSinceLastUpdate = newUpdateTimeSinceLastUpdate;
}

int OpenglWidget::updateTimeSinceLastUpdate() const
{
    return m_updateTimeSinceLastUpdate;
}
