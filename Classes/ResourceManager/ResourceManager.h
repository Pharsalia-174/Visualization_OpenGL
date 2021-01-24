//
// Created by Pharsalia on 2020/4/23.
//

#ifndef OPENGL_CLION_TESTA_RESOURCEMANAGER_H
#define OPENGL_CLION_TESTA_RESOURCEMANAGER_H

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <Texture2D/Texture2D.h>

class ResourceManager {
//TODO:资源管理类,负责完成资源的读取和存储及存档相关内容,初版暂不考虑打包加密等内容
public:
    //读取Path指定的文件并以字符串形式返回
    static std::string readFile(const char* path);
    //读取Path指定的图片 返回形成的Texture2D对象
    static Texture2D readTexture(const char* path);

};


#endif //OPENGL_CLION_TESTA_RESOURCEMANAGER_H
