#ifndef MODELTREEWGT_H
#define MODELTREEWGT_H

#include <QWidget>
#include <QList>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "canvas/onemodelwidget.h"
namespace Ui {
class ModelTreeWgt;
}

class Model;

class ModelTreeWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ModelTreeWgt(QWidget *parent = nullptr);
    ~ModelTreeWgt();

    void addModel(Model* model);
private:
    QList <Model*> m_models;
    QList <OneModelWidget*> m_modelWgts;
    Ui::ModelTreeWgt *ui;
};

#endif // MODELTREEWGT_H
