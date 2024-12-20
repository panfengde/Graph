//
// Created by 潘峰 on 2024/11/1.
//
#include "GraphAPI.h"
#include <iostream>



void* aWindow = nullptr;

void testAPI(){

}

#if defined(__ANDROID__)
typedef struct {
    GLuint program;
    GLuint vertexBuffer;
    GLuint vertexArray;
    GLuint indexBuffer;

    GLint modelLocation;
    GLint viewProjLocation;

    double lastTouchX;
    double lastTouchY;

    double angleX;
    double angleY;

    bool needsRedraw;
} TouchApp;

void* Graph::createWindow(void*display, unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT)
{
    auto aDisplay=(GLFMDisplay *)display;

    TouchApp *app = static_cast<TouchApp *>(calloc(1, sizeof(TouchApp)));
    //颜色混合
    glEnable(GL_BLEND);
    //glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glEnable(GL_LINE_SMOOTH);//开启抗锯齿功能

    // glEnable(GL_DEPTH_TEST);

    //glEnable(GL_CULL_FACE);//开启表⾯面剔除(默认背⾯面剔除)
    /*//裁剪测试设置
    glScissor(0, 0, 500, 500);
    glEnable(GL_SCISSOR_TEST);*/

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glfmSetDisplayConfig(aDisplay,
                         GLFMRenderingAPIOpenGLES32,
                         GLFMColorFormatRGBA8888,
                         GLFMDepthFormatNone,
                         GLFMStencilFormatNone,
                         GLFMMultisampleNone);

    glfmSetUserData(aDisplay, app);
    return aDisplay;
}
#else
void* Graph::createWindow(void*display,unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return window;
    }

    glfwMakeContextCurrent(window);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }
    return window;
}
#endif

