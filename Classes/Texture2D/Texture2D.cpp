//
// Created by Pharsalia on 2020/5/1.
//

#include "Texture2D.h"

Texture2D::Texture2D(int ImageFormat, int InternalFormat, GLuint Wrap_S, GLuint Wrap_T, GLuint Filter_Min, GLuint Filter_Max) {
    ID = 0;
    iWidth = 0; iHeight = 0;
    this->iImageFormat = ImageFormat;
    this->iInternalFormat = InternalFormat;
    this->Wrap_S = Wrap_S;
    this->Wrap_T = Wrap_T;
    this->Filter_Max = Filter_Min;
    this->Filter_Min = Filter_Max;
    glGenTextures(1,&ID);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1,&ID);
}

void Texture2D::Generate(int width, int height, unsigned char *data) {
    this->iWidth = width;
    this->iHeight = height;
    //创建纹理
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, iInternalFormat, iWidth, iHeight, 0, iImageFormat, GL_UNSIGNED_BYTE, data);
    //设置环绕方式及过滤模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    //生成mipmap 解绑
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const {
    glActiveTexture(ID);
    glBindTexture(GL_TEXTURE_2D, ID);
}


unsigned int Texture2D::getId() const {
    return ID;
}

int Texture2D::getWidth() const {
    return iWidth;
}

int Texture2D::getHeight() const {
    return iHeight;
}

int Texture2D::getImageFormat() const {
    return iImageFormat;
}

int Texture2D::getInternalFormat() const {
    return iInternalFormat;
}

GLuint Texture2D::getWrapS() const {
    return Wrap_S;
}

GLuint Texture2D::getWrapT() const {
    return Wrap_T;
}

GLuint Texture2D::getFilterMin() const {
    return Filter_Min;
}

GLuint Texture2D::getFilterMax() const {
    return Filter_Max;
}

void Texture2D::setFormat(int format) {
    Texture2D::iImageFormat = format;
    Texture2D::iInternalFormat = format;
}

void Texture2D::setImageFormat(int ImageFormat) {
    Texture2D::iImageFormat = ImageFormat;
}

void Texture2D::setInternalFormat(int InternalFormat) {
    Texture2D::iInternalFormat = InternalFormat;
}

void Texture2D::setWrapS(GLuint wrapS) {
    Wrap_S = wrapS;
}

void Texture2D::setWrapT(GLuint wrapT) {
    Wrap_T = wrapT;
}

void Texture2D::setFilterMin(GLuint filterMin) {
    Filter_Min = filterMin;
}

void Texture2D::setFilterMax(GLuint filterMax) {
    Filter_Max = filterMax;
}
