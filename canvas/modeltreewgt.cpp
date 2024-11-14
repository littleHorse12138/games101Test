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
    OneModelWidget* wgt = new OneModelWidget(model, this);
    m_modelWgts.append(wgt);
    ui->m_pVLay->addWidget(wgt);
}

