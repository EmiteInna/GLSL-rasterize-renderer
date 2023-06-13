#ifndef EMITEINNA_HEAD
#define EMITEINNA_HEAD
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>
#include "shaderh.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "RenderObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include <Windows.h>
#include "imm.h"
#include <algorithm>
#include "Texture.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void InitializeObjects();
void RenderFunctions();
void Pause();
GLFWwindow* InitializeGL();
/*
* Mouse Info
*/
GLFWwindow* window;
Camera* maincam;
Light* mainLight;
int size = 5;
RenderObject* renderObjects[512];
Material* materials[512];
glm::vec3 cameraPosition = glm::vec3(0,10,10);
glm::vec3 cameraTarget = glm::vec3(0, -1, -1);
glm::vec3 cameraUp = glm::vec3(0, 1, 0);
bool haveReadMouse = false;
float lastxpos = 0, lastypos = 0;
float pitch=-45, yaw=-90;

float axisWidth = 0.01;
float axisLength = 20;

float deltime = 0;
float lastframe = 0;
float positions[][3] = {
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0}
};
float rotations[][3] = {
    {0 ,45,0},
    {0,0,0},
    {0,0,0},
    {0,0,0}
};
float scales[][3] = {
    {1,1,1},
    {1,1,1},
    {1,1,1},
    {1,1,1}
};
float vertices[][2048] = {
    {
    //正面
    0.5f, 0.5f, 0.5f,0,  1,1,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,   // 右上角
    0.5f, -0.5f, 0.5f,0,   1,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 右下角
    -0.5f, -0.5f, 0.5f,0,  0,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 左下角
    -0.5f, 0.5f, 0.5f,0,   0,1,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 左上角
    //背面
    -0.5f, 0.5f, -0.5f,0,  1,1,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,  
    -0.5f, -0.5f, -0.5f,0,   1,0,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    0.5f, -0.5f, -0.5f,0,  0,0,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    0.5f, 0.5f, -0.5f,0,   0,1,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    //右面
    0.5f, 0.5f, -0.5f,0,  1,1,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    0.5f, -0.5f, -0.5f,0,   1,0,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    0.5f, -0.5f, 0.5f,0,  0,0,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    0.5f, 0.5f, 0.5f,0,   0,1,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    //左面
    -0.5f, 0.5f, 0.5f,0,  1,1,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -0.5f, -0.5f, 0.5f,0,   1,0,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -0.5f, -0.5f, -0.5f,0,  0,0,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -0.5f, 0.5f, -0.5f,0,   0,1,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    //上面
    0.5f, 0.5f, -0.5f,0,  1,1,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    0.5f, 0.5f, 0.5f,0,   1,0,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    -0.5f, 0.5f, 0.5f,0,  0,0,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    -0.5f, 0.5f, -0.5f,0,   0,1,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    //下
    -0.5f, -0.5f, -0.5f,0,  1,1,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    -0.5f, -0.5f, 0.5f,0,   1,0,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    0.5f, -0.5f, 0.5f,0,  0,0,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    0.5f, -0.5f, -0.5f,0,   0,1,0,0,  0,-1  ,0,0,  0,0,0,0,  0,0,0,0,
    },
    {
        //正面
     axisLength, axisWidth, axisWidth,0,  1,1,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,   // 右上角
     axisLength, -axisWidth, axisWidth,0,   1,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 右下角
     -axisWidth, -axisWidth, axisWidth,0,  0,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 左下角
     -axisWidth, axisWidth, axisWidth,0,   0,1,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 左上角
     //背面
     -axisWidth, axisWidth, -axisWidth,0,  1,1,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
     -axisWidth, -axisWidth, -axisWidth,0,   1,0,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
     axisLength, -axisWidth, -axisWidth,0,  0,0,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
     axisLength, axisWidth, -axisWidth,0,   0,1,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
     //右面
     axisLength, axisWidth, -axisWidth,0,  1,1,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
     axisLength, -axisWidth, -axisWidth,0,   1,0,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
     axisLength, -axisWidth, axisWidth,0,  0,0,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
     axisLength, axisWidth, axisWidth,0,   0,1,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
     //左面
     -axisWidth, axisWidth, axisWidth,0,  1,1,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
     -axisWidth, -axisWidth, axisWidth,0,   1,0,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
     -axisWidth, -axisWidth, -axisWidth,0,  0,0,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
     -axisWidth, axisWidth, -axisWidth,0,   0,1,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
     //上面
     axisLength, axisWidth, -axisWidth,0,  1,1,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
     axisLength, axisWidth, axisWidth,0,   1,0,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
     -axisWidth, axisWidth, axisWidth,0,  0,0,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
     -axisWidth, axisWidth, -axisWidth,0,   0,1,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
     //下
     -axisWidth, -axisWidth, -axisWidth,0,  1,1,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
     -axisWidth, -axisWidth, axisWidth,0,   1,0,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
     axisLength, -axisWidth, axisWidth,0,  0,0,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
     axisLength, -axisWidth, -axisWidth,0,   0,1,0,0,  0,-1  ,0,0,  0,0,0,0,  0,0,0,0,
    },
    {
        //正面
    axisWidth, axisLength, axisWidth,0,  1,1,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,   // 右上角
    axisWidth, -axisWidth, axisWidth,0,   1,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 右下角
    -axisWidth, -axisWidth, axisWidth,0,  0,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 左下角
    -axisWidth, axisLength, axisWidth,0,   0,1,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 左上角
    //背面
    -axisWidth, axisLength, -axisWidth,0,  1,1,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, -axisWidth, -axisWidth,0,   1,0,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, -axisWidth,0,  0,0,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    axisWidth, axisLength, -axisWidth,0,   0,1,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    //右面
    axisWidth,axisLength, -axisWidth,0,  1,1,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, -axisWidth,0,   1,0,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, axisWidth,0,  0,0,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, axisLength, axisWidth,0,   0,1,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    //左面
    -axisWidth, axisLength, axisWidth,0,  1,1,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, -axisWidth, axisWidth,0,   1,0,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, -axisWidth, -axisWidth,0,  0,0,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, axisLength, -axisWidth,0,   0,1,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    //上面
    axisWidth, axisLength, -axisWidth,0,  1,1,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, axisLength, axisWidth,0,   1,0,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, axisLength, axisWidth,0,  0,0,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, axisLength, -axisWidth,0,   0,1,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    //下
    -axisWidth, -axisWidth, -axisWidth,0,  1,1,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, -axisWidth, axisWidth,0,   1,0,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, axisWidth,0,  0,0,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, -axisWidth,0,   0,1,0,0,  0,-1  ,0,0,  0,0,0,0,  0,0,0,0,
    },
    {
        //正面
    axisWidth, axisWidth, axisLength,0,  1,1,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,   // 右上角
    axisWidth, -axisWidth, axisLength,0,   1,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 右下角
    -axisWidth, -axisWidth, axisLength,0,  0,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 左下角
    -axisWidth, axisWidth, axisLength,0,   0,1,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,// 左上角
    //背面
    -axisWidth, axisWidth, -axisWidth,0,  1,1,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, -axisWidth, -axisWidth,0,   1,0,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, -axisWidth,0,  0,0,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    axisWidth, axisWidth, -axisWidth,0,   0,1,0,0,  0,0,-1,0,  0,0,0,0,  0,0,0,0,
    //右面
    axisWidth, axisWidth, -axisWidth,0,  1,1,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, -axisWidth,0,   1,0,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth,axisLength,0,  0,0,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, axisWidth, axisLength,0,   0,1,0,0,  1,0,0,0,  0,0,0,0,  0,0,0,0,
    //左面
    -axisWidth, axisWidth, axisLength,0,  1,1,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, -axisWidth, axisLength,0,   1,0,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, -axisWidth, -axisWidth,0,  0,0,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, axisWidth, -axisWidth,0,   0,1,0,0,  -1,0,0,0,  0,0,0,0,  0,0,0,0,
    //上面
    axisWidth, axisWidth, -axisWidth,0,  1,1,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, axisWidth, axisLength,0,   1,0,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, axisWidth, axisLength,0,  0,0,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, axisWidth, -axisWidth,0,   0,1,0,0,  0,1,0,0,  0,0,0,0,  0,0,0,0,
    //下
    -axisWidth, -axisWidth, -axisWidth,0,  1,1,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    -axisWidth, -axisWidth, axisWidth,0,   1,0,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, axisWidth,0,  0,0,0,0,  0,-1,0,0,  0,0,0,0,  0,0,0,0,
    axisWidth, -axisWidth, -axisWidth,0,   0,1,0,0,  0,-1  ,0,0,  0,0,0,0,  0,0,0,0,
    }
};

unsigned int indices[][512] = {
    {
    0,1,3,
    1,2,3,
    4,5,7,
    5,6,7,
    8,9,11,
    9,10,11,
    12,13,15,
    13,14,15,
    16,17,19,
    17,18,19,
    20,21,23,
    21,22,23

    },
     {
    0,1,3,
    1,2,3,
    4,5,7,
    5,6,7,
    8,9,11,
    9,10,11,
    12,13,15,
    13,14,15,
    16,17,19,
    17,18,19,
    20,21,23,
    21,22,23

    },
     {
    0,1,3,
    1,2,3,
    4,5,7,
    5,6,7,
    8,9,11,
    9,10,11,
    12,13,15,
    13,14,15,
    16,17,19,
    17,18,19,
    20,21,23,
    21,22,23

    },
     {
    0,1,3,
    1,2,3,
    4,5,7,
    5,6,7,
    8,9,11,
    9,10,11,
    12,13,15,
    13,14,15,
    16,17,19,
    17,18,19,
    20,21,23,
    21,22,23

    }
};
unsigned int attris[512]{
    1,1,1
};
bool paused=false;
void Pause() {
    paused = !paused;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); 
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (haveReadMouse == false) {
        haveReadMouse = true;
        lastxpos = xpos;
        lastypos = ypos;
    }
    else {
        float xoffset = xpos - lastxpos;
        float yoffset =- ypos + lastypos;
        lastxpos = xpos;
        lastypos = ypos;
        float sensitivity = 0.1f; 
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        yaw += xoffset;
        pitch += yoffset;
        pitch = std::min(pitch,1.0f* 85);
        pitch = std::max(pitch, -1.0f * 85);
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        maincam->target = glm::normalize(front);
    }
  //  maincam->showinfo();
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    float fov = maincam->FOV-(float)yoffset;
    fov = std::max(1.0f, fov);
    fov = std::min(45.0f, fov);
    maincam->FOV = fov;
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        Pause();
    } 
    float cameraSpeed = 2.5f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        maincam->position += cameraSpeed * maincam->target*deltime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        maincam->position += cameraSpeed * -maincam->target * deltime;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        maincam->position += cameraSpeed * maincam->up * deltime;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        maincam->position += cameraSpeed * -maincam->up * deltime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        maincam->position += cameraSpeed * maincam->Right * deltime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        maincam->position += cameraSpeed * -maincam->Right * deltime;
    
}
GLFWwindow* InitializeGL() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //新建一个窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    //调用GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }
    //设置视口和回调函数
  //  glViewport(0, 0, 800, 600);
    HWND hwnd = glfwGetWin32Window(window); // 将窗口句柄赋值给hwnd
    HIMC hIMC = ImmGetContext(hwnd);
    ImmAssociateContext(hwnd, NULL);
    ImmReleaseContext(hwnd, hIMC);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//设置鼠标不显示
    maincam = new Camera(cameraPosition, cameraTarget, cameraUp, 45, 1.33, 0.1, 100);
    mainLight = new Light(glm::vec3(0,1,1), glm::vec3(1,1,1));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//绑定事件
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    return window;
}
void UpdateTime() {
    float current = glfwGetTime();
    deltime = current - lastframe;
    lastframe = current;
}
void InitializeObjects() {
    materials[0] = new Material("0000.vs", "0000.fr",1);
    materials[0]->setTexture(0, "baseMap", "kyaru.jpg");
    for (int i = 1; i < 4; i++) {
        materials[i] = new Material("0001.vs", "0001.fr",0);
    }
    materials[4] = new Material("0000.vs", "0000.fr", 1);
    Texture spaceMap("spacecraftbasemap.png");
    materials[4]->setTexture(0,"baseMap", spaceMap);
    materials[1]->setFloat3("baseColor", glm::vec3(1, 0, 0));
    materials[2]->setFloat3("baseColor", glm::vec3(0, 1, 0));
    materials[3]->setFloat3("baseColor", glm::vec3(0, 0, 1));
    for(int i=0;i<4;i++)
       renderObjects[i] = new RenderObject(vertices[i], indices[i],24,36,positions[i],rotations[i],scales[i],materials[i],maincam,mainLight);
    
    renderObjects[4] = new RenderObject("spacecraft.fbx", materials[4], maincam, mainLight, false);
}
void ReleaseObjects() {
    for (int i = 0; i < size; i++) {
        renderObjects[i]->DeleteObject();
    }
}
void RenderFunctions() {
    if (paused)return;
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    int x, y;
    glfwGetFramebufferSize(window, &x, &y);
    maincam->aspect = (float)x / (float)y;
    
    for (int i = 0; i < size; i++) {
        glEnable(GL_DEPTH_TEST);
        if (i == 0)continue;
        renderObjects[i]->Render();

    }
    glfwSwapBuffers(window);//交换缓存数组，可以看做滚动数组
    glfwPollEvents();//时间检查
}

int __chap1()
{
    window=InitializeGL();
    if (window == NULL)return -1;
    InitializeObjects();
    //渲染循环
    while (!glfwWindowShouldClose(window)) {
        maincam->UpdateCamera();
        processInput(window);
        UpdateTime();
        //渲染指令start
        RenderFunctions();
        
        //end
       
    }
    ReleaseObjects();
    glfwTerminate();
    return 0;
}
int main() {
    
    return __chap1();
}
#endif // !EMITEINNA_HEAD



