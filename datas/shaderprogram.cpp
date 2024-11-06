#include "shaderprogram.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include <QMatrix4x4>
#include <canvas/openglwidget.h>
ShaderProgram::ShaderProgram() {
    init();
}

void ShaderProgram::init()
{
    initializeOpenGLFunctions();
    setVertexPath("C:/Users/Administrator/Documents/Games101Test/resc/shader/BlingPhoneVertex.txt");
    setFragPath("C:/Users/Administrator/Documents/Games101Test/resc/shader/BlingPhoneFragment.txt");
    loadShaders();
    createVertexShader();
    createFragmentShader();
    createShader();
}

void ShaderProgram::use()
{
    glUseProgram(m_shaderProgramID);
}

void ShaderProgram::unUse()
{
    glUseProgram(0);
}

void ShaderProgram::setBool(QString name, bool data)
{
    glUniform1i(glGetUniformLocation(m_shaderProgramID, name.toStdString().c_str()), data);
}

void ShaderProgram::setInt(QString name, int data)
{
    glUniform1i(glGetUniformLocation(m_shaderProgramID, name.toStdString().c_str()), data);
}

void ShaderProgram::setFloat(QString name, float data)
{    
    glUniform1f(glGetUniformLocation(m_shaderProgramID, name.toStdString().c_str()), data);
}

void ShaderProgram::setMatrix(QString name, QMatrix4x4 data)
{
    auto matrixAsFloatArray = data.constData();
    auto location = glGetUniformLocation(m_shaderProgramID, name.toStdString().c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, matrixAsFloatArray);
}

void ShaderProgram::setVec3(QString name, QVector3D data)
{
    glUniform3f(glGetUniformLocation(m_shaderProgramID, name.toStdString().c_str()), data[0], data[1], data[2]);
}

void ShaderProgram::createShader()
{
    int success;
    m_shaderProgramID = glCreateProgram();
    glAttachShader(m_shaderProgramID, m_vertexShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);
    glLinkProgram(m_shaderProgramID);
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

int ShaderProgram::vbo() const
{
    return m_vbo;
}

void ShaderProgram::setVbo(int newVbo)
{
    m_vbo = newVbo;
}

void ShaderProgram::initializeGL()
{
    initializeOpenGLFunctions();
}

int ShaderProgram::vao() const
{
    return m_vao;
}

void ShaderProgram::setVao(int newVao)
{
    m_vao = newVao;
}

QString ShaderProgram::fragPath() const
{
    return m_fragPath;
}

void ShaderProgram::setFragPath(const QString &newFragPath)
{
    m_fragPath = newFragPath;
}

QString ShaderProgram::vertexPath() const
{
    return m_vertexPath;
}

void ShaderProgram::setVertexPath(const QString &newVertexPath)
{
    m_vertexPath = newVertexPath;
}

int ShaderProgram::fragmentShaderID() const
{
    return m_fragmentShaderID;
}

void ShaderProgram::setFragmentShaderID(int newFragmentShaderID)
{
    m_fragmentShaderID = newFragmentShaderID;
}

int ShaderProgram::vertexShaderID() const
{
    return m_vertexShaderID;
}

void ShaderProgram::setVertexShaderID(int newVertexShaderID)
{
    m_vertexShaderID = newVertexShaderID;
}

void ShaderProgram::createVertexShader()
{
    int success;
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderID, 1, &m_vertexData, NULL);
    glCompileShader(m_vertexShaderID);
    glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(m_vertexShaderID, 512, NULL, infoLog);
        qDebug() << "init vertex error" << infoLog;
    }
}

void ShaderProgram::createFragmentShader()
{
    int success;
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderID, 1, &m_fragmentData, NULL);
    glCompileShader(m_fragmentShaderID);
    glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(m_fragmentShaderID, 512, NULL, infoLog);
        qDebug() << "init fragment error" << infoLog;
        qDebug() << "frag data" << m_fragmentData;
    }
}

void ShaderProgram::loadShaders()
{
    // 1. 从文件路径中获取顶点/片段着色器
    auto vertexPath = m_vertexPath.toStdString();
    auto fragmentPath = m_fragPath.toStdString();
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    m_fragmentData = fShaderCode;
    m_vertexData = vShaderCode;
}

void BlingPhoneShader::init()
{
    setVertexPath(":/resc/shader/BlingPhoneFragment.vert");
    setFragPath(":/resc/shader/BlingPhoneFragment.frag");
    ShaderProgram::init();
}
