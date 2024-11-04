//
// Created by 潘峰 on 2024/11/4.
//

#ifndef GRAPHENV_H
#define GRAPHENV_H
#if defined(__ANDROID__)
#include "glfm.h"
#include <gles3/gl32.h>
#else
#include <glad/include/glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#endif //GRAPHENV_H
