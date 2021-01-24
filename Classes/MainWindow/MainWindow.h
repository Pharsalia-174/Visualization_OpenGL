//
// Created by Pharsalia on 2020/4/13.
//

#ifndef OPENGL_TEST_MAINWINDOW_H
#define OPENGL_TEST_MAINWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class MainWindow {
private:
    GLFWwindow* pMainWindow;        //窗口指针
    GLFWwindow* tempWindow;         //全屏化时的缓冲指针
    int iWidth;                     //窗口长度
    int iHeight;                    //窗口宽度
    const char* c_szTile;           //窗口标题 对应显示的字符串
    bool bWindowInitialized;        //窗口是否成功完成初始化
    bool bWindowVisible;            //窗口是否可见
    GLFWmonitor* pMonitor;          //窗口当前所在显示器指针
    bool bWindowResizable;          //是否可由用户调整窗口大小
    bool bWindowAspectRatio;        //是否启用长宽比限制
    int nNumeratorOfAspectRatio;    //固定长宽比时的长度比例(分母)
    int nDenominatorOfAspectRatio;  //固定长宽比时的长度比例(分子)
    bool bWindowedFullScreen;       //是否为全屏窗口模式
    bool bVSync;                    //是否开启垂直同步
    float fXScale;                  //X轴DPI缩放比例
    float fYScale;                  //Y轴DPI缩放比例

    //构造时根据提供的信息初始化OpenGL组件及主窗口
    void initWindow(bool showWindow = false);
    //缓冲区大小调整时的回调函数
    static void framebuffer_size_calledback(GLFWwindow* window, int width, int height);

public:
    //构造 析构
    explicit MainWindow(const char* title, int width = 1600, int height = 900, bool resizable = true, bool visible = true);
    ~MainWindow();
    //设置标题 图标
    void setTitle(const char* title);
    void setIcon(const char* iconDir);
    //设置是否启用固定长宽比 是否启用垂直同步 是否显示窗口
    void setAspectRatio(bool enableAspectRatio = true, int numerator = 16, int denominator = 9);
    void setVSync(bool VSync = true);
    void showWindow(bool visible = true);
    //设置全屏窗口
    void setWindowedFullScreen(bool windowedFullScreen = true);

/*  Getter  */
public:
    GLFWwindow *getWindowPointer() const;
    GLFWmonitor *getMonitorPointer() const;

    int getWidth() const;
    int getHeight() const;
    const char *getTile() const;
    bool isWindowInitialized() const;
    bool isWindowVisible() const;
    bool isWindowResizable() const;
    bool isWindowAspectRatio() const;
    int getNumeratorOfAspectRatio() const;
    int getDenominatorOfAspectRatio() const;
    bool isWindowedFullScreen() const;
    bool isVSync() const;
    float getXScale() const;
    float getYScale() const;
};


#endif //OPENGL_TEST_MAINWINDOW_H
