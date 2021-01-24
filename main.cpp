#include "tools.h"

int main() {
    //创建主窗口
    MainWindow mainWindow("TestWindow",1600,900, true);
    mainWindow.setIcon(R"(E:\Engine\Cache\testIcon-160x160.png)");
    mainWindow.setAspectRatio();
    mainWindow.setVSync();
    //mainWindow.setWindowedFullScreen();
    GLFWwindow* window = mainWindow.getWindowPointer();

    //创建着色器
    Shader testShader;
    const char* vShaderSource = R"(E:\Engine\Visualization_OpenGL\Shaders\BaseShader\VertexShader.glsl)";
    const char* fShaderSource = R"(E:\Engine\Visualization_OpenGL\Shaders\BaseShader\FragmentShader.glsl)";
    testShader.Compile(vShaderSource, fShaderSource);

    //读取图片
    const char* texturePath = R"(E:\Engine\Cache\KMR.jpg)";
    Texture2D texture = ResourceManager::readTexture(texturePath);

    //读取顶点数据
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };;
    VerticesInfo v = {true, true, 36};

    //生成精灵
    Sprite sprite(vertices, &v);
    sprite.Generate();

    //启用深度测试
    glEnable(GL_DEPTH_TEST);

    /*
    //顶点数组 用以将数据传入VBO
    float vertices[] = {
             //顶点坐标            //纹理坐标
             1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // 右上角
             1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // 右下角
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // 左下角
            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // 左上角
    };
    VerticesInfo v = {true, true, 4};

    //索引缓冲对象 EBO 用于绘制多个三角形时从数组指定顶点
    unsigned int indices[] = {
            0, 1, 3, // 左上三角形
            1, 2, 3  // 左下三角形
    };
    IndicesInfo i = {true, 2, 6};

    //生成精灵对象
    Sprite sprite(vertices, &v, indices, &i);
    sprite.Generate();
    */

    //3D空间矩阵
    glm::mat4 model = glm::mat4(1.0f);      //模型矩阵 对应于世界空间
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);       //观察矩阵 对应于摄像机位置 摄像机前进等同于空间的后移 再对应到当前矩阵上
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::mat4(1.0f); //投影矩阵 用于实现透视效果
    projection = glm::perspective(glm::radians(45.0f), 1600.0f/900.0f, 0.1f, 100.0f);

    //渲染循环 跳出条件为当前窗口为关闭状态 将状态设置为关闭不会立刻关闭窗口
    while (!glfwWindowShouldClose(window)) {
        //时间变量
        auto timeValue = (float)glfwGetTime();
        std::cout<< fps_stats() <<std::endl;

        //输入处理
        glfwSetKeyCallback(window, key_callback);

        //激活着色器
        testShader.use();

        //随时间旋转
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        //设置至三维空间中
        testShader.setMatrix4("model",      1, GL_FALSE, glm::value_ptr(model));
        testShader.setMatrix4("view",       1, GL_FALSE, glm::value_ptr(view));
        testShader.setMatrix4("projection", 1, GL_FALSE, glm::value_ptr(projection));

        //淡入淡出
        float tempF[4] = {1.0f,1.0f,1.0f,1.0f};
        tempF[0] = (float)sin(timeValue);
        tempF[1] = (float)cos(timeValue);
        tempF[2] = (float)sin(timeValue) + (float)cos(timeValue);
        testShader.setFloat4("colorVector",4,tempF);

        //设置背景颜色 清除深度缓冲
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //绘制
        sprite.Bind();
        texture.Bind();
        sprite.Draw();

        //检测并调用事件，交换缓存
        glfwSwapBuffers(window);  //使用双缓冲解决闪屏现象
        glfwPollEvents();	      //检测事件 处理事件 (调用回调函数)
    }

    return 0;
}

void processInput(GLFWwindow* window) {
    //限制触发次数示例
    static bool flag = false;
    static float temp = 0;
    static float startTime;
    if(!flag){
        startTime = (float) glfwGetTime();
        temp = 0;
        flag = true;
    }else{
        temp += (float) glfwGetTime() - startTime;
        if(temp >= 0.5){
            flag = false;
        } else{
            return;
        }
    }
    //TODO:实现按下松开状态切换标记

    //获取当前窗口状态下该按键是否被摁下
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        //设置关闭状态为true
        //glfwSetWindowShouldClose(window, true);
        //TODO: 修改为按下ESC时(自己加时间间隔) 切换绘制模式
        changePolygonMode();
    }
}

void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
    if(key == GLFW_KEY_A && action == GLFW_PRESS) changePolygonMode();
}

void changePolygonMode(){
    int temp;
    glGetIntegerv(GL_POLYGON_MODE, &temp);
    if(temp == GL_FILL){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

int fps_stats()
{
    static int fps_total = 0;
    static int fps = 0;
    static int t = std::clock();
    ++fps;
    if(std::clock() - t > 1000)
    {
        fps_total = fps;
        fps = 0;
        t = std::clock();
    }
    return fps_total;
}