cmake_minimum_required(VERSION 3.15)
project(Visualization_OpenGL)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/Classes)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(Visualization_OpenGL
                src/glad.c src/stb_image.h src/stb_image_implementation.cpp
                main.cpp tools.h data.h
                Shaders/ShaderLoader.cpp Shaders/ShaderLoader.h
                Classes/MainWindow/MainWindow.cpp
                Classes/ResourceManager/ResourceManager.cpp
                Classes/Shader/Shader.cpp
                Classes/Sprite/Sprite.cpp
                Classes/Texture2D/Texture2D.cpp)

target_link_libraries(Visualization_OpenGL ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)