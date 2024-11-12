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
    qDebug() << "mousepress";
    if(ev->buttons() == Qt::LeftButton){
        qDebug() << "删除";
        auto model = MDM->root()->children()[0];
        int fn = model->pMesh()->faceNum();
        int cnt = fn / 5;
        for(int i = 0; i < cnt; i++){
            model->pMesh()->removeFace(model->pMesh()->faceHandleList().last());
        }
        model->pMesh()->setNormalColor(QVector4D(0,1,1,1));
        model->updateMeshToShader();
    }else if(ev->buttons() == Qt::MiddleButton){
        qDebug() << "新建";
        buildNewModel();

    }
    m_lastMousePlace = ev->pos();
    return;
    if(ev->buttons() == Qt::LeftButton){
        QList <Model*> np;
        np.push_back(MDM->root()->children()[0]);
        if(Intersection::isMouseIntersection(np, ev->pos(), m_pViewer)){
            qDebug() << "拾取到了";

            auto model = MDM->root()->children()[0];
            int fn = model->pMesh()->faceNum();
            int cnt = fn / 5;
            for(int i = 0; i < cnt; i++){
                model->pMesh()->removeFace(model->pMesh()->faceHandleList().last());
            }
             model->updateMeshToShader();

            // {
            //     GLint flags;
            //     glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
            //     if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            //         // 上下文是调试上下文
            //         qDebug() << "tiaoshi yes2";
            //     }else{
            //         qDebug() << "tiaoshi no2" << glGetString(GL_VERSION);
            //     }
            //     Model* newModel = GenerateModelTool::generateBall();
            //     SM->bindToBlingPhoneShader(newModel, m_pViewer);
            //     newModel->updateMeshToShader();
            //     m_pViewer->updateAllDataToShader(newModel);
            //     newModel->pMesh()->setNormalColor(QVector4D(0,0,1,1));
            //     MDM->addModel(newModel);
            // }

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
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        // 上下文是调试上下文
        qDebug() << "tiaoshi yes1";
    }else{
        qDebug() << "tiaoshi no1" << glGetString(GL_VERSION);
    }
    // {
    //     Model* newModel = new Model;
    //     MDM->readMesh(newModel->pMesh(), "C:/test1/test.obj");
    //     SM->bindToBlingPhoneShader(newModel, m_pViewer);
    //     newModel->pMesh()->setNormalColor(QVector4D(0,1,0,1));
    //     newModel->updateMeshToShader();
    //     m_pViewer->updateAllDataToShader(newModel);
    //     MDM->addModel(newModel);
    // }
    // buildNewModel();


    // qDebug() << "删除";
    // auto model = MDM->root()->children()[0];
    // int fn = model->pMesh()->faceNum();
    // int cnt = fn / 5;
    // for(int i = 0; i < cnt; i++){
    //     model->pMesh()->removeFace(model->pMesh()->faceHandleList().last());
    // }
    // model->pMesh()->setNormalColor(QVector4D(0,1,1,1));
    // model->updateMeshToShader();


}

void OpenglWidget::buildNewModel()
{
    {
        qDebug() << "step 0";
        glUseProgram(0);
        qDebug() << "step 1";
        Model* newModel = GenerateModelTool::generateBall();
        qDebug() << "step 2";
        SM->bindToBlingPhoneShader(newModel, m_pViewer);
        newModel->pShader()->use();
        qDebug() << "step 3";
        newModel->updateMeshToShader();
        qDebug() << "step 4";
        m_pViewer->updateAllDataToShader(newModel);
        qDebug() << "step 5";
        newModel->pMesh()->setNormalColor(QVector4D(0,0,1,1));
        qDebug() << "step 6";
        MDM->addModel(newModel);
        qDebug() << "step 7";
    }
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
