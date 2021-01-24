//
// Created by Pharsalia on 2020/4/23.
//

#ifndef OPENGL_CLION_TESTA_SHADER_H
#define OPENGL_CLION_TESTA_SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    explicit Shader();
    ~Shader();
    void use() const;
    unsigned int getId() const;
    bool isCompiled() const;
    //输入源码并编译
    void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
    //传入Uniform参数
    void setFloat4(const std::string &name, int num, const GLfloat* values);
    void setMatrix4(const std::string &name, int num, GLboolean transpose, const GLfloat* values);
private:
    unsigned int ID;    //标识符
    bool bCompiled;     //是否已完成编译
    //检查编译错误
    void checkCompileErrors(unsigned object, const std::string& type);
};


#endif //OPENGL_CLION_TESTA_SHADER_H
