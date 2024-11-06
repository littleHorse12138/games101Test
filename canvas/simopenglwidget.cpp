#include "simopenglwidget.h"
#include "datas/camera.h"
#include "datas/model.h"
#include <QPainter>
SimOpenglWidget::SimOpenglWidget(QWidget *parent, Model *model, Camera *camera): QWidget{parent}
{
    m_pModel = model;
    m_pCamera = camera;
    // update();
}

void SimOpenglWidget::paintEvent(QPaintEvent *ev)
{
    if(!m_pModel){
        return;
    }
    QPainter painter(this);
    int cnt = 0;
    auto data = m_pModel->pMesh()->getVertices();
    int l = data.size() / 9;
    qDebug() << "size" << l << data.size();
    float w = width() / 2.0;
    float h = height() / 2.0;
    while(cnt < l-1){
        QPointF pos[3];
        for(int i = 0; i < 3; i++){
            float x = data[cnt*9 + 0];
            float y = data[cnt*9 + 1];
            float z = data[cnt*9 + 2];
            QVector3D p;
            p = QVector3D(x,y,z);
            p = m_pCamera->getPerspectiveMatrix() * (m_pCamera->getViewMatrix() * p);
            p[0] = (p[0] + 1) * w;
            p[1] = (2-(p[1] + 1)) * h;
            pos[i] = QPointF(p[0], p[1]);
            cnt++;
        }
        painter.drawLine(pos[0], pos[1]);
        painter.drawLine(pos[1], pos[2]);
        painter.drawLine(pos[2], pos[0]);

    }
}
