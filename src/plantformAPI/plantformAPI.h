//
// Created by 潘峰 on 2024/11/1.
//
#ifndef PLANTFORMAPI_H
#define PLANTFORMAPI_H
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#if defined(__ANDROID__)
#include "registerMethod.h"
#endif


std::string getSaticResourcesPath();

std::string getExecutablePath();

std::string CrossPlatformReadFile(const char* filename);
#endif //PLANTFORMAPI_H
