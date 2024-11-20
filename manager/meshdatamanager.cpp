#include "meshdatamanager.h"
#include "tool/tool.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QVector3D>
MeshDataManager::MeshDataManager(QObject *parent)
    : QObject{parent}
{
    init();
}

MeshDataManager *MeshDataManager::getInstance()
{
    static MeshDataManager* instance = nullptr;
    if(!instance){
        instance= new MeshDataManager;
    }
    return instance;
}

void MeshDataManager::writeMesh(MeshData *data, QString path)
{
    if(!data){
        return;
    }
    FileTool::createFileOrDir(path);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Cannot open file for write");
        return;
    }

    QTextStream in(&file);
    for(auto vh: data->vertexHandleList()){
        auto pos = data->vertex(vh)->pos();
        QString str = "v ";
        str += QString::number(pos[0]);
        str += " ";
        str += QString::number(pos[1]);
        str += " ";
        str += QString::number(pos[2]);
        in << str << Qt::endl;
    }

    for(auto fh: data->faceHandleList()){
        auto f = data->face(fh);
        auto index0 = data->vertexHandleList().indexOf(f->vh(0));
        auto index1 = data->vertexHandleList().indexOf(f->vh(1));
        auto index2 = data->vertexHandleList().indexOf(f->vh(2));
        QString str = "f ";
        str += QString::number(index0 + 1);
        str += " ";
        str += QString::number(index1 + 1);
        str += " ";
        str += QString::number(index2 + 1);
        in << str << Qt::endl;
    }
}

bool MeshDataManager::readMesh(MeshData *data, QString path)
{
    if(!data){
        data = new MeshData(nullptr);
    }
    auto suffix = Tool::suffix(path);
    if(suffix == "obj"){
        return readObj(data, path);
    }else{
        return false;
    }
}

void MeshDataManager::addModel(Model *model)
{
    m_models.append(model);
    m_root->addChild(model);
}

void MeshDataManager::init()
{
    m_root = new Model;
}

bool MeshDataManager::readObj(MeshData *data, QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "读取失败";
        return false;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        auto line = in.readLine();
        auto list = line.split(" ");
        if(list.empty()){
            continue;
        }
        if(list[0] == "v"){
            QVector3D v(list[1].toFloat(), list[2].toFloat(), list[3].toFloat());
            data->addVertex(v);
        }else if(list[0] == "f"){
            for(auto &l: list){
                l = l.split("/").first();
            }

            data->addFace(data->vertexHandle(list[1].toInt() - 1),
                          data->vertexHandle(list[2].toInt() - 1),
                          data->vertexHandle(list[3].toInt() - 1));
            // if(list.size() == 5){
            //     data->addFace(data->vertexHandle(list[1].toInt() - 1),
            //                   data->vertexHandle(list[3].toInt() - 1),
            //                   data->vertexHandle(list[4].toInt() - 1));
            // }
        }else if(list[0] == "g" && list[1] == "object_2"){
            break;
        }
    }

    return true;
}

Model *MeshDataManager::root() const
{
    return m_root;
}

void MeshDataManager::setRoot(Model *newRoot)
{
    m_root = newRoot;
}

int MeshDataManager::getAllRenderPointNum(Model* model)
{
    int an = 0;
    if(model && model->pShader() && model->nodeMask()){
        an += model->pMesh()->faceNum() * 3;
    }
    for(auto child: model->children()){
        an += getAllRenderPointNum(child);
    }
    return an;
}
