//
// Created by Pharsalia on 2020/4/6.
//

#ifndef OPENGL_CLION_TESTA_SHADERLOADER_H
#define OPENGL_CLION_TESTA_SHADERLOADER_H

#include "../tools.h"

class ShaderLoader {
public:
    //唯一指定ID
    unsigned int ID;
    //构造函数 编译着色器 链接生成着色器程序 默认从shader文件夹中查找源码
    //顶点着色器文件路径:vertexPath
    //片段着色器文件路径:fragmentPath
    ShaderLoader(const char* vertexPath, const char* fragmentPath);
    //使用着色器
    void use();
    //获取着色器ID用以使用Uniform参数
    unsigned int getId() const;
};


#endif //OPENGL_CLION_TESTA_SHADERLOADER_H
