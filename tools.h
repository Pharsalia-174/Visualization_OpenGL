#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <ctime>

#include <MainWindow/MainWindow.h>
#include <ResourceManager/ResourceManager.h>
#include <Shader/Shader.h>
#include <Sprite/Sprite.h>
#include <Texture2D/Texture2D.h>


//按键监控函数
void processInput(GLFWwindow* window);
//绘制模式切换函数
void changePolygonMode();
//glfw键盘事件回调函数
static void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods);
//获取FPS
int fps_stats();
