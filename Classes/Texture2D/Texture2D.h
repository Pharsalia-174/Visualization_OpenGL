//
// Created by Pharsalia on 2020/5/1.
//

#ifndef OPENGL_CLION_TESTA_TEXTURE2D_H
#define OPENGL_CLION_TESTA_TEXTURE2D_H

#include <glad/glad.h>

class Texture2D {
private:
    unsigned int ID;        //标识符
    int iWidth;             //材质长度
    int iHeight;            //材质宽度
    int iImageFormat;       //图片读取格式(RGB或RGBA)
    int iInternalFormat;    //内部存储格式(RGB或RGBA)
    GLuint Wrap_S;          //环绕方式_X轴方向
    GLuint Wrap_T;          //环绕方式_Y轴方向
    GLuint Filter_Min;      //过滤模式_缩小
    GLuint Filter_Max;      //过滤模式_放大
public:
    explicit Texture2D(
            int ImageFormat = GL_RGB,
            int InternalFormat = GL_RGB,
            GLuint Wrap_S = GL_CLAMP_TO_BORDER,
            GLuint Wrap_T = GL_CLAMP_TO_BORDER,
            GLuint Filter_Min = GL_LINEAR_MIPMAP_LINEAR,
            GLuint Filter_Max = GL_LINEAR);
    ~Texture2D();
    //根据资源管理器读取的数据及提前设置的参数生成对应的纹理材质
    void Generate(int width, int height, unsigned char* data);
    //将操作对象改变为当前纹理
    void Bind() const;
/* Getter and Setter */
public:
    unsigned int getId() const;
    int getWidth() const;
    int getHeight() const;
    int getImageFormat() const;
    int getInternalFormat() const;
    GLuint getWrapS() const;
    GLuint getWrapT() const;
    GLuint getFilterMin() const;
    GLuint getFilterMax() const;

    void setFormat(int format);
    void setImageFormat(int ImageFormat);
    void setInternalFormat(int InternalFormat);
    void setWrapS(GLuint wrapS);
    void setWrapT(GLuint wrapT);
    void setFilterMin(GLuint filterMin);
    void setFilterMax(GLuint filterMax);
};


#endif //OPENGL_CLION_TESTA_TEXTURE2D_H
