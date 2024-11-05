#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <QString>
#include "qopenglfunctions_3_3_core.h"
class ShaderProgram: public QOpenGLFunctions_3_3_Core
{
public:
    ShaderProgram();

    virtual void init();

    virtual void use(); //开始使用
    virtual void unUse(); //停止使用

    virtual void setBool(QString name, bool data);
    virtual void setInt(QString name, int data);
    virtual void setFloat(QString name, float data);
    virtual void setMatrix(QString name, QMatrix4x4 data);

    int vertexShaderID() const;
    void setVertexShaderID(int newVertexShaderID);

    int fragmentShaderID() const;
    void setFragmentShaderID(int newFragmentShaderID);

    QString vertexPath() const;
    void setVertexPath(const QString &newVertexPath);

    QString fragPath() const;
    void setFragPath(const QString &newFragPath);

    int vao() const;
    void setVao(int newVao);

    int vbo() const;
    void setVbo(int newVbo);

    virtual void initializeGL();

protected:
    //初始化相关
    void loadShaders(); //读取文件里的shader
    void createVertexShader();
    void createFragmentShader();
    void createShader(); //初始化shaderID

private:
    QString m_vertexPath;
    QString m_fragPath;

    const char* m_vertexData;
    const char* m_fragmentData;

    int m_shaderProgramID;
    int m_vertexShaderID;
    int m_fragmentShaderID;

    std::string vertexCode;
    std::string fragmentCode;

    int m_vao;
    int m_vbo;

};


class BlingPhoneShader: public ShaderProgram
{
public:
    virtual void init();
};

#endif // SHADERPROGRAM_H
