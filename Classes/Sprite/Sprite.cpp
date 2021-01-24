//
// Created by Pharsalia on 2020/9/24.
//

#include <iostream>
#include "Sprite.h"

Sprite::Sprite(const float *vertices, VerticesInfo* info1, const unsigned int *indices, IndicesInfo* info2) {
    //顶点数组为必选项
    if(vertices && info1){
        this->verticesInfo = {info1->isExist, info1->containTexture, info1->vertexNum};
        //获取长度
        int length = (verticesInfo.containTexture?5:3) * verticesInfo.vertexNum;
        //转录数组
        pVertices = new float[length];
        for(int i = 0; i<length; i++){
            pVertices[i] = vertices[i];
            //std::cout<<pVertices[i]<<" ";
        }
        //std::cout<<std::endl;
        bLegal = true;
    }
    //索引数组为可选项
    if(indices && info2){
        this->indicesInfo = {info2->isExist, info2->triangleNum, info2->totalVertexNum};
        //获取长度
        int length = indicesInfo.triangleNum * 3;
        //转录数组
        pIndices = new unsigned int[length];
        for(int i = 0;i<length;i++){
            pIndices[i] = indices[i];
            //std::cout<<pIndices[i]<<" ";
        }
        //std::cout<<info2->isExist<<std::endl;
    }
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1,&ID);
    if(pVertices){
        try {
            delete pVertices;
        }catch(std::exception &e){
            return;
        }
    }
    if(pIndices){
        try {
            delete pIndices;
        }catch(std::exception &e){
            return;
        }
    }
}

bool Sprite::Generate() {
    //std::cout<<bLegal<<std::endl;
    if(!bLegal) return false;
    int paramNum = verticesInfo.containTexture?5:3;
    //选定上下文
    unsigned int VBO,EBO;
    glGenVertexArrays(1,&ID);
    glBindVertexArray(ID);
    //生成VBO 绑定 传入数据
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*verticesInfo.vertexNum*paramNum, pVertices, dataStoreType);
    //生成EBO 绑定 传入数据
    if(indicesInfo.isExist){
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*indicesInfo.triangleNum*3, pIndices, dataStoreType);
    }
    //声明数据组成结构 激活顶点
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,paramNum*sizeof(float),(void*)nullptr);
    glEnableVertexAttribArray(0);
    //附着材质到顶点着色器中
    if(verticesInfo.containTexture){
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    //解绑VAO
    glBindVertexArray(0);
    bGenerated = true;
    return true;
}

bool Sprite::Bind() {
    if(bGenerated){
        glBindVertexArray(ID); return true;
    }
    return false;
}

bool Sprite::Draw() {
    if(bGenerated){
        if(indicesInfo.isExist){
            glDrawElements(drawMode, indicesInfo.totalVertexNum, GL_UNSIGNED_INT, nullptr);
        }else{
            glDrawArrays(drawMode, 0, verticesInfo.vertexNum);
        }
        return true;
    }
    return false;
}

GLenum Sprite::getDataStoreType() const {
    return dataStoreType;
}

void Sprite::setDataStoreType(GLenum dataStoreType) {
    Sprite::dataStoreType = dataStoreType;
}

GLenum Sprite::getDrawMode() const {
    return drawMode;
}

void Sprite::setDrawMode(GLenum drawMode) {
    Sprite::drawMode = drawMode;
}

const VerticesInfo &Sprite::getVerticesInfo() const {
    return verticesInfo;
}

const IndicesInfo &Sprite::getIndicesInfo() const {
    return indicesInfo;
}

unsigned int Sprite::getId() const {
    return ID;
}

bool Sprite::isBLegal() const {
    return bLegal;
}

bool Sprite::isBGenerated() const {
    return bGenerated;
}
