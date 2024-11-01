//
// Created by 潘峰 on 2024/11/1.
//

#ifndef GRAPHAPI_H
#define GRAPHAPI_H
#include <functional>
#if defined(__ANDROID__)
#include "glfm.h"
#else
#include <glad/include/glad/glad.h>
#include <GLFW/glfw3.h>
#endif



typedef std::function<void()> renderCallBack;
void testAPI();

extern void* aWindow ;

namespace Graph
{
    void* createWindow(void *,unsigned int width=100, unsigned int height=100);

    class Shader;
}

namespace WindowsEvent
{
    void envSetCharCallback();
    void envSetScrollCallback();
    void envSetCursorPosCallback();
    void envSetMouseButtonCallback();
}


#endif //GRAPHAPI_H
