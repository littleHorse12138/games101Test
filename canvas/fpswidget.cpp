#include "fpswidget.h"
#include "ui_fpswidget.h"
#include "openglwidget.h"
FpsWidget::FpsWidget(OpenglWidget* openglWgt, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FpsWidget)
{
    ui->setupUi(this);
    m_pParWgt = openglWgt;
    init();
}

FpsWidget::~FpsWidget()
{
    delete ui;
}

void FpsWidget::init()
{
    m_pUpdateTimer = new QTimer;
    connect(m_pUpdateTimer, &QTimer::timeout, this, &FpsWidget::onTimerUpdateTimeout);
    m_pUpdateTimer->start(1000);
}

void FpsWidget::onTimerUpdateTimeout()
{
    QString text = "FPS:" + QString::number(m_pParWgt->updateTimeSinceLastUpdate());
    ui->m_pLabFps->setText(text);
    m_pParWgt->setUpdateTimeSinceLastUpdate(0);
}
