// Example app that draws a cube.
// The cube can be rotated via touch, scroll wheel, or keyboard arrow keys.
#include "GraphEnv.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "GraphAPI/Shader.h"
#include "plantformAPI/plantformAPI.h"
#include "GraphAPI/GraphAPI.h"
#include "registerMethod.h"

Graph::Shader* aShader;
//顶点缓冲对象(Vertex Buffer Objects, VBO)
unsigned int VBO, VAO;

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

static void onSurfaceCreated(GLFMDisplay *display, int width, int height) {
    GLFMRenderingAPI api = glfmGetRenderingAPI(display);
    printf("Hello from GLFM! Using OpenGL %s\n",
           api == GLFMRenderingAPIOpenGLES32 ? "ES 3.2" :
           api == GLFMRenderingAPIOpenGLES31 ? "ES 3.1" :
           api == GLFMRenderingAPIOpenGLES3 ? "ES 3.0" : "ES 2.0");
}

static void onSurfaceRefresh(GLFMDisplay *display) {
    TouchApp *app = static_cast<TouchApp *>(glfmGetUserData(display));
    app->needsRedraw = true;
}

static void onSurfaceDestroyed(GLFMDisplay *display) {
    // When the surface is destroyed, all existing GL resources are no longer valid.
    TouchApp *app = static_cast<TouchApp *>(glfmGetUserData(display));
    app->program = 0;
    app->vertexBuffer = 0;
    app->vertexArray = 0;
    app->indexBuffer = 0;
    printf("Goodbye\n");
}

static void draw(TouchApp *app, int width, int height) {
    if(aShader== nullptr){
        aShader = new Graph::Shader("vertexShader_es.vs","fragmentShader_es.fs");

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, // left
                0.5f, -0.5f, 0.0f, // right
                0.0f, 0.5f, 0.0f // top
        };


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    glViewport(0, 0, width, height);
    glClearColor(0.9f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // input
    // -----
    aShader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Draw background
}

static void onDraw(GLFMDisplay *display) {
    TouchApp *app = static_cast<TouchApp *>(glfmGetUserData(display));
    if (app->needsRedraw) {
        app->needsRedraw = true;
        int width, height;
        glfmGetDisplaySize(display, &width, &height);
        draw(app, width, height);
        glfmSwapBuffers(display);
    }
}

void testCppWithJava(){
    CrossPlatformPrint("go---------------------");
    std::string hello = readAssetFile("labCode.lab");
    CrossPlatformPrint(hello);
    std::string test("1----------------------glfmMain------------------");
    CrossPlatformPrint(test);
}

void setBool(const std::string &name, bool value)  {
    glUniform1i(glGetUniformLocation(0, name.c_str()), (int) value);
}

void glfmMain(GLFMDisplay *display) {
    testCppWithJava();
    CrossPlatformPrint("go-okoko--------------------");
    CrossPlatformPrint("go-okoko--------------------");


    auto result = CrossPlatformReadFile("labCode.lab");
    std::cout << "result:" << std::endl;
    std::cout << result << std::endl;

    /*TouchApp *app = static_cast<TouchApp *>(calloc(1, sizeof(TouchApp)));

    glfmSetDisplayConfig(display,
                         GLFMRenderingAPIOpenGLES32,
                         GLFMColorFormatRGBA8888,
                         GLFMDepthFormatNone,
                         GLFMStencilFormatNone,
                         GLFMMultisampleNone);*/
    auto app = (TouchApp *)Graph::createWindow(display,0, 0);



    glfmSetUserData(display, app);
    //glfmSetSurfaceCreatedFunc(display, onSurfaceCreated);


    glfmSetSurfaceRefreshFunc(display, onSurfaceRefresh);
    glfmSetSurfaceDestroyedFunc(display, onSurfaceDestroyed);
    glfmSetRenderFunc(display, onDraw);
}