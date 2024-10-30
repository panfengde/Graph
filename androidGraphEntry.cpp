// Example app that draws a cube.
// The cube can be rotated via touch, scroll wheel, or keyboard arrow keys.
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "glfm.h"
#include "./registerMethod/registerMethod.h"

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
    static float rNumber = 0.0f;
    static float gNumber = 0.0f;
    static float bNumber = 0.0f;
    rNumber += 0.002;
    gNumber += 0.004;
    bNumber += 0.006;
    if (rNumber > 1)rNumber = 0;
    if (gNumber > 1)gNumber = 0;
    if (bNumber > 1)bNumber = 0;
    // Draw background
    glViewport(0, 0, width, height);
    glClearColor(rNumber, gNumber, bNumber, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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
    CrossPlatformPrint("go-okoko--------------------");
    CrossPlatformPrint("go-okoko--------------------");
    TouchApp *app = static_cast<TouchApp *>(calloc(1, sizeof(TouchApp)));

    glfmSetDisplayConfig(display,
                         GLFMRenderingAPIOpenGLES32,
                         GLFMColorFormatRGBA8888,
                         GLFMDepthFormatNone,
                         GLFMStencilFormatNone,
                         GLFMMultisampleNone);


    glfmSetUserData(display, app);
    glfmSetSurfaceCreatedFunc(display, onSurfaceCreated);
    glfmSetSurfaceRefreshFunc(display, onSurfaceRefresh);
    glfmSetSurfaceDestroyedFunc(display, onSurfaceDestroyed);
    glfmSetRenderFunc(display, onDraw);
}