//
// Created by Pharsalia on 2020/4/23.
//

#include "ResourceManager.h"
#include "../src/stb_image.h"
using namespace std;

string ResourceManager::readFile(const char* path) {
    string sCode;
    ifstream sFile;
    sFile.exceptions(ifstream::failbit | ifstream::badbit);
    stringstream sStream;
    try{
        sFile.open(path);
        sStream << sFile.rdbuf();
        sFile.close();
        sCode = sStream.str();
    } catch (ifstream::failure &e) {
        cout << "ERROR::RESOURCE::FILE_NOT_SUCCESSFULLY_READ" << endl;
    }
    return sCode;
}

Texture2D ResourceManager::readTexture(const char* path) {
    Texture2D texture;
    unsigned char* data;
    int width, height, nrChannels, format;
    //获取参数 读取图片数据
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path,&width,&height,&nrChannels,0);
    //根据色彩通道设置读取格式
    if(data){
        format = (nrChannels == 3)?GL_RGB:GL_RGBA;
        texture.setFormat(format);
        texture.Generate(width, height, data);
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放资源
    stbi_image_free(data);
    return texture;
}
