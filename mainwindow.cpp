#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    m_pOpenglWidget = OpenglWidget::getInstance();
    ui->m_pVLay->addWidget(m_pOpenglWidget);
    ui->m_pToolWidget->setPOpenglWidget(m_pOpenglWidget);
    m_pOpenglWidget->setPModelTreeWgt(ui->m_pModelTreeWIdget);
    connectSignalAndSlots();
    // ui->m_pOpenglWIdget->buildNewModel();
}

void MainWindow::connectSignalAndSlots()
{

}
