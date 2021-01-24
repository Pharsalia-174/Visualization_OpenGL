//
// Created by Pharsalia on 2020/4/23.
//

#include <iostream>
#include <ResourceManager/ResourceManager.h>
#include "Shader.h"


unsigned int Shader::getId() const {
    return ID;
}

bool Shader::isCompiled() const {
    return bCompiled;
}

Shader::Shader() {
    ID = 0;
    bCompiled = false;
}

Shader::~Shader() {
    glDeleteProgram(ID);
}


void Shader::use() const {
    if(bCompiled) glUseProgram(ID);
}

void Shader::Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
    //文件读取
    std::string vertexCode = ResourceManager::readFile(vertexSource);
    const char* vShaderCode = vertexCode.data();
    std::string fragmentCode = ResourceManager::readFile(fragmentSource);
    const char* fShaderCode = fragmentCode.data();
    //几何着色器单独处理
    std::string geometryCode;
    const char *gShaderCode = nullptr;
    if(geometrySource != nullptr){
        geometryCode = ResourceManager::readFile(geometrySource);
        gShaderCode = geometryCode.data();
    }

    //着色器临时ID
    unsigned int sVertex, sFragment, sGeometry;

    //顶点着色器
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vShaderCode, nullptr);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    //片段着色器
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fShaderCode, nullptr);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    //几何着色器
    if(geometrySource != nullptr){
        sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(sGeometry, 1, &gShaderCode, nullptr);
        glCompileShader(sGeometry);
        checkCompileErrors(sGeometry, "GEOMETRY");
    }

    //链接 生成ID
    this->ID = glCreateProgram();
    glAttachShader(ID, sVertex);
    glAttachShader(ID, sFragment);
    if(geometrySource != nullptr)
        glAttachShader(ID, sGeometry);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    //清除缓存
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if(geometrySource != nullptr)
        glDeleteShader(sGeometry);
    bCompiled = true;
}

void Shader::checkCompileErrors(unsigned int object, const std::string& type) {
    int success;
    char infoLog[1024];
    if(type != "PROGRAM"){
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cout<<"| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }else{
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

void Shader::setFloat4(const std::string &name, int num, const GLfloat* values) {
    GLint location = glGetUniformLocation(ID,name.c_str());
    //由于OpenGL没有这玩意 只能自己整一个
    switch(num){
        case 1:
            glUniform1f(location,values[0]);
            break;
        case 2:
            glUniform2f(location,values[0],values[1]);
            break;
        case 3:
            glUniform3f(location,values[0],values[1],values[2]);
            break;
        case 4:
            glUniform4f(location,values[0],values[1],values[2],values[3]);
            break;
        default:
            std::cout<<"ERROR::UNIFORM::NUMBER_INVALID"<<std::endl;
        }
}

void Shader::setMatrix4(const std::string &name, int num, GLboolean transpose, const GLfloat *values) {
    glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()), num, transpose, values);
}
