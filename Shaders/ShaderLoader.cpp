//
// Created by Pharsalia on 2020/4/6.
//

#include "ShaderLoader.h"

void ShaderLoader::use() {
    glUseProgram(ID);
}

unsigned int ShaderLoader::getId() const {
    return ID;
}

ShaderLoader::ShaderLoader(const char *vertexPath, const char *fragmentPath) {
    //从文件读取源码
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    //设置立即抛出的异常类型
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        //打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream,fShaderStream;
        //采用文件流读取文件
        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();
        //关闭文件
        vShaderFile.close();
        fShaderFile.close();
        //将数据流转移到字符串中
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.data();
    const char* fShaderCode = fragmentCode.data();

    //编译 链接
    unsigned int vertexID,fragmentID;
    int success;
    char infoLog[512];
    //编译顶点着色器
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID,1,&vShaderCode,nullptr);
    glCompileShader(vertexID);
    glGetShaderiv(vertexID,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexID,512,nullptr,infoLog);
        std::cout<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<infoLog<<std::endl;
    }
    //编译片段着色器
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID,1,&fShaderCode,nullptr);
    glCompileShader(fragmentID);
    glGetShaderiv(fragmentID,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentID,512,nullptr,infoLog);
        std::cout<< "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<infoLog<<std::endl;
    }
    //链接
    ID = glCreateProgram();
    glAttachShader(ID,vertexID);
    glAttachShader(ID,fragmentID);
    glLinkProgram(ID);
    glGetShaderiv(ID,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(ID,512,nullptr,infoLog);
        std::cout<< "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<infoLog<<std::endl;
    }
    //清除无用着色器
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}
