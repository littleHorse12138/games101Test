#include "modeltreewgt.h"
#include "ui_modeltreewgt.h"


#include "datas/model.h"
ModelTreeWgt::ModelTreeWgt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModelTreeWgt)
{
    ui->setupUi(this);
}

ModelTreeWgt::~ModelTreeWgt()
{
    delete ui;
}

void ModelTreeWgt::addModel(Model *model)
{
    OneModelWgt* wgt = new OneModelWgt(model, this);
    m_modelWgts.append(wgt);
}

OneModelWgt::OneModelWgt(Model *model, QWidget *par):QWidget(par)
{
    qDebug() << "to gouzao hanshu";

    m_pModel = model;
    init();
}

void OneModelWgt::init()
{
    m_pLabName = new QLabel;
    m_pBtnShow = new QPushButton;
    m_pMainLay = new QGridLayout;

    m_pLabName->setText(m_pModel->name());
    m_pBtnShow->setText("展示");
    m_pBtnShow->setCheckable(true);

    setLayout(m_pMainLay);
    m_pMainLay->addWidget(m_pBtnShow, 1, 0);
    m_pMainLay->addWidget(m_pLabName, 1, 1);

    connect(m_pBtnShow, &QPushButton::clicked, this, &OneModelWgt::onBtnShowClicked);
}

void OneModelWgt::onBtnShowClicked()
{
    if(m_pBtnShow->isChecked()){
        m_pBtnShow->setText("展示");
        m_pModel->setNodeMask(1);
    }else{
        m_pBtnShow->setText("隐藏");
        m_pModel->setNodeMask(0);
    }
}
