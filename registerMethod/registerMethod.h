//
// Created by 59546 on 2024/9/17.
//

#ifndef TESTLAB_REGISTERMETHOD_H
#define TESTLAB_REGISTERMETHOD_H
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __ANDROID__
#include <android/log.h>
#endif

std::string readAssetFile(const char *filename);

void CrossPlatformPrint(const std::string& message) ;



#endif //TESTLAB_REGISTERMETHOD_H
