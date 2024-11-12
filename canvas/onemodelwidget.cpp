#include "onemodelwidget.h"
#include "ui_onemodelwidget.h"

OneModelWidget::OneModelWidget(Model* model,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OneModelWidget)
{
    ui->setupUi(this);
    m_pModel = model;
    init();
}

OneModelWidget::~OneModelWidget()
{
    delete ui;
}

void OneModelWidget::init()
{
    ui->m_pBtnExpand->setCheckable(true);
    ui->m_pBtnShowOrHide->setCheckable(true);
    ui->m_pBtnShowBoundingBox->setCheckable(true);
    ui->m_pBtnShowGrid->setCheckable(true);

    ui->m_pBtnExpand->setChecked(false);
    ui->m_pBtnShowOrHide->setChecked(false);
    ui->m_pBtnShowBoundingBox->setChecked(false);
    ui->m_pBtnShowGrid->setChecked(false);

    onBtnShowGridClicked();
    onBtnShowBoundingBoxClicked();
    onBtnShowOrHideClicked();
    onBtnExpandlicked();

    connectSignalAndSlots();
}

void OneModelWidget::connectSignalAndSlots()
{
    connect(ui->m_pBtnExpand, &QPushButton::clicked, this, &OneModelWidget::onBtnExpandlicked);
    connect(ui->m_pBtnShowOrHide, &QPushButton::clicked, this, &OneModelWidget::onBtnShowOrHideClicked);
    connect(ui->m_pBtnShowGrid, &QPushButton::clicked, this, &OneModelWidget::onBtnShowGridClicked);
    connect(ui->m_pBtnShowBoundingBox, &QPushButton::clicked, this, &OneModelWidget::onBtnShowBoundingBoxClicked);
}

void OneModelWidget::onBtnExpandlicked()
{
    if(ui->m_pBtnExpand->isChecked()){
        ui->m_pBtnExpand->setText("收起");
        ui->m_pWgtFunction->show();
    }else{
        ui->m_pBtnExpand->setText("展开");
        ui->m_pWgtFunction->hide();
    }
}

void OneModelWidget::onBtnShowOrHideClicked()
{
    if(ui->m_pBtnShowOrHide->isChecked()){
        ui->m_pBtnShowOrHide->setText("展示");
        m_pModel->setNodeMask(1);
    }else{
        ui->m_pBtnShowOrHide->setText("隐藏");
        m_pModel->setNodeMask(0);
    }
}

void OneModelWidget::onBtnShowGridClicked()
{
    if(ui->m_pBtnShowBoundingBox->isChecked()){

    }else{

    }
}

void OneModelWidget::onBtnShowBoundingBoxClicked()
{
    if(ui->m_pBtnShowGrid->isChecked()){

    }else{

    }
}

