//
// Created by Pharsalia on 2020/9/24.
//

#ifndef OPENGL_CLION_TESTA_SPRITE_H
#define OPENGL_CLION_TESTA_SPRITE_H

#include <glad/glad.h>

//顶点数组信息结构体
struct VerticesInfo{
    bool isExist;           //是否存在顶点数组
    bool containTexture;    //是否包含纹理信息 (对应列数 3/5)
    int vertexNum;          //顶点个数 (对应行数)
};

//索引数组信息结构体
struct IndicesInfo{
    bool isExist;       //是否存在索引数组
    int triangleNum;    //索引数组中三角形的数量
    int totalVertexNum; //实际绘制的顶点数
};

//未指定形状的精灵 作为基类
class Sprite {
private:
    unsigned int ID{};                //ID 用于获取VAO VBO和EBO为可变动的ID
    //顶点数组
    float* pVertices = nullptr;
    //顶点数组信息
    VerticesInfo verticesInfo{false, false, 0};
    //索引数组
    unsigned int* pIndices = nullptr;
    //索引数组信息
    IndicesInfo indicesInfo{false, 0};
    bool bLegal = false;                    //当前精灵信息是否完备
    bool bGenerated = false;                //精灵是否完成了绑定
    GLenum dataStoreType = GL_STATIC_DRAW;  //数组信息的存储方式 正确的设置可以起到优化作用
    GLenum drawMode = GL_TRIANGLES;         //绘制时使用的图元
public:
    explicit Sprite(const float* vertices, VerticesInfo* info1, const unsigned int* indices = nullptr, IndicesInfo* info2 = nullptr);
    ~Sprite();
    //TODO:设置索引数组信息

    //生成
    bool Generate();
    //绑定
    bool Bind();
    //绘制
    bool Draw();

/* Getter and Setter */
public:
    unsigned int getId() const;

    const VerticesInfo &getVerticesInfo() const;
    const IndicesInfo &getIndicesInfo() const;

    GLenum getDataStoreType() const;
    void setDataStoreType(GLenum dataStoreType);

    GLenum getDrawMode() const;
    void setDrawMode(GLenum drawMode);

    bool isBLegal() const;
    bool isBGenerated() const;
};


#endif //OPENGL_CLION_TESTA_SPRITE_H
