//
// Created by Pharsalia on 2020/4/13.
//

#include <iostream>
#include "MainWindow.h"
#include "../src/stb_image.h"

void MainWindow::framebuffer_size_calledback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

MainWindow::MainWindow(const char *title, int width, int height, bool resizable, bool visible) {
    //根据参数设置窗口参数
    iWidth = width; iHeight = height;
    c_szTile = title;
    bWindowResizable = resizable;
    //默认为16:9的长宽比 且不指定长宽比模式
    bWindowAspectRatio = false;
    nNumeratorOfAspectRatio = 16;
    nDenominatorOfAspectRatio = 9;
    fXScale = 1; fYScale = 1;
    //默认不使用全屏 不启用垂直同步
    bWindowedFullScreen = false;
    bVSync = false;
    //设置指针到空指针 设置状态
    pMainWindow = nullptr;
    tempWindow = nullptr;
    pMonitor = nullptr;
    bWindowInitialized = false;
    bWindowVisible = false;
    //调用初始化
    initWindow(visible);
}

MainWindow::~MainWindow() {
    glfwTerminate();
}

void MainWindow::initWindow(bool showWindow) {
    //初始化GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    //根据构造函数初步创建窗口
    glfwWindowHint(GLFW_VISIBLE,GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE,bWindowResizable);
    pMainWindow = glfwCreateWindow(iWidth, iHeight, c_szTile, nullptr, nullptr);
    if (pMainWindow == nullptr) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return;
    }
    //设置上下文及改变窗口大小时缓冲区大小调整的回调函数 默认关闭垂直同步
    glfwMakeContextCurrent(pMainWindow);
    glfwSetFramebufferSizeCallback(pMainWindow, framebuffer_size_calledback);
    glfwSwapInterval(0);
    //初始化GLAD
    if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    //完成初始化 显示窗口(可选)
    bWindowInitialized = true;
    bWindowVisible = showWindow;
    //设置主要显示器及缩放比例
    pMonitor = glfwGetPrimaryMonitor();
    glfwGetMonitorContentScale(pMonitor,&fXScale,&fYScale);
    if(showWindow) glfwShowWindow(pMainWindow);
}

void MainWindow::setTitle(const char *title) {
    if(title) glfwSetWindowTitle(pMainWindow,title);
}

void MainWindow::setIcon(const char* iconDir) {
    if(!iconDir) return;
    //读取图标 格式不正确的图片会导致无法启动
    GLFWimage icon[1]; int temp;
    icon[0].pixels = stbi_load(iconDir,&icon[0].width,&icon[0].height, nullptr,4);
    if(!icon[0].pixels) std::cout << "Failed to load icon from file "<< iconDir << std::endl;
    //设置窗口图标
    glfwSetWindowIcon(pMainWindow, 1, icon);
    //清除图片缓存
    stbi_image_free(icon[0].pixels);
}

void MainWindow::setAspectRatio(bool enableAspectRatio, int numerator, int denominator) {
    //覆写数据
    nNumeratorOfAspectRatio = numerator>0 ? numerator : 16;
    nDenominatorOfAspectRatio = denominator>0 ? denominator : 9;
    bWindowAspectRatio = enableAspectRatio;
    //是否启用固定高宽比
    if(enableAspectRatio) glfwSetWindowAspectRatio(pMainWindow, nNumeratorOfAspectRatio, nDenominatorOfAspectRatio);
    else glfwSetWindowAspectRatio(pMainWindow, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void MainWindow::setVSync(bool VSync) {
    bVSync = VSync;
    if(VSync) glfwSwapInterval(1);
    else glfwSwapInterval(0);
}

void MainWindow::showWindow(bool visible) {
    bWindowVisible = visible;
    if(visible) glfwShowWindow(pMainWindow);
    else glfwHideWindow(pMainWindow);
}

//TODO: 解决上限60FPS的问题
void MainWindow::setWindowedFullScreen(bool windowedFullScreen) {
    bWindowedFullScreen = windowedFullScreen;
    if(windowedFullScreen){
        const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);
        glfwSetWindowMonitor(pMainWindow,pMonitor,0,0,mode->width,mode->height,mode->refreshRate);
        setVSync(bVSync);
    }else{
        glfwSetWindowMonitor(pMainWindow, nullptr,0,0,iWidth,iHeight,GLFW_DONT_CARE);
        setVSync(bVSync);
    }
}


GLFWwindow *MainWindow::getWindowPointer() const {
    return pMainWindow;
}

int MainWindow::getWidth() const {
    return iWidth;
}

int MainWindow::getHeight() const {
    return iHeight;
}

const char *MainWindow::getTile() const {
    return c_szTile;
}

bool MainWindow::isWindowInitialized() const {
    return bWindowInitialized;
}

bool MainWindow::isWindowVisible() const {
    return bWindowVisible;
}

GLFWmonitor *MainWindow::getMonitorPointer() const {
    return pMonitor;
}

bool MainWindow::isWindowResizable() const {
    return bWindowResizable;
}

bool MainWindow::isWindowAspectRatio() const {
    return bWindowAspectRatio;
}

int MainWindow::getNumeratorOfAspectRatio() const {
    return nNumeratorOfAspectRatio;
}

int MainWindow::getDenominatorOfAspectRatio() const {
    return nDenominatorOfAspectRatio;
}

bool MainWindow::isWindowedFullScreen() const {
    return bWindowedFullScreen;
}

bool MainWindow::isVSync() const {
    return bVSync;
}

float MainWindow::getXScale() const {
    return fXScale;
}

float MainWindow::getYScale() const {
    return fYScale;
}
