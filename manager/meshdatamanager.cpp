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

bool MeshDataManager::readMesh(MeshData *data, QString path)
{
    if(!data){
        data = new MeshData(nullptr);
    }
    auto suffix = Tool::suffix(path);
    qDebug() << "suffix" << suffix;
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
