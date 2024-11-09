#include "onemodelwidget.h"
#include "ui_onemodelwidget.h"

OneModelWidget::OneModelWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OneModelWidget)
{
    ui->setupUi(this);
}

OneModelWidget::~OneModelWidget()
{
    delete ui;
}
