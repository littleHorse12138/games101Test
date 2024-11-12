#include "toolwidget.h"
#include "ui_toolwidget.h"
#include "canvas/openglwidget.h"
ToolWidget::ToolWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolWidget)
{
    ui->setupUi(this);
    init();
}

ToolWidget::~ToolWidget()
{
    delete ui;
}

void ToolWidget::init()
{
    connectSignalAndSlots();
}

void ToolWidget::connectSignalAndSlots()
{
    connect(ui->m_pBtnShowSimShader, &QPushButton::clicked, this, &ToolWidget::onBtnSimShaderClicked);
}

void ToolWidget::onBtnSimShaderClicked()
{
    m_pOpenglWidget->buildNewModel();
}

OpenglWidget *ToolWidget::pOpenglWidget() const
{
    return m_pOpenglWidget;
}

void ToolWidget::setPOpenglWidget(OpenglWidget *newPOpenglWidget)
{
    m_pOpenglWidget = newPOpenglWidget;
}
