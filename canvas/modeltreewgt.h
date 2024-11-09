#ifndef MODELTREEWGT_H
#define MODELTREEWGT_H

#include <QWidget>
#include <QList>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
namespace Ui {
class ModelTreeWgt;
}

class Model;

class OneModelWgt:public QWidget
{
public:
    OneModelWgt(Model* model, QWidget* par = nullptr);
protected:
    void init();

    void onBtnShowClicked();
private:
    Model* m_pModel = nullptr;

    QGridLayout* m_pMainLay = nullptr;
    QPushButton* m_pBtnShow = nullptr;
    QLabel* m_pLabName = nullptr;
};

class ModelTreeWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ModelTreeWgt(QWidget *parent = nullptr);
    ~ModelTreeWgt();

    void addModel(Model* model);
private:
    QList <Model*> m_models;
    QList <OneModelWgt*> m_modelWgts;
    Ui::ModelTreeWgt *ui;
};

#endif // MODELTREEWGT_H
