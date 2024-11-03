//
// Created by 潘峰 on 2024/11/1.
//

#include "plantformAPI.h"
#include <iostream>
#include <filesystem>
//不能在头文件引用下面的include，因为byte重复定义了
#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <mach-o/dyld.h>
#include <string>
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#undef byte
#else
#endif


namespace fs = std::filesystem;
std::string getSaticResourcesPath() {
    static std::string result;
#ifdef __APPLE__
    if (result.empty()) {
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
        char resourcesPath[PATH_MAX];
        if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *) resourcesPath, PATH_MAX)) {
            // error!
            std::cout << "error Path: " << resourcesPath << std::endl;
        }

        CFRelease(resourcesURL);
        chdir(resourcesPath);
        result = resourcesPath;
    }
    return result;
#elif defined(_WIN32) || defined(_WIN64)
    if (result.empty()) {
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(nullptr, szPath, MAX_PATH);
        result = std::string(szPath);

        fs::path exePath(szPath);
        if (fs::exists(exePath.parent_path() / "LUI")) {
            //开发模式下
            result = (exePath.parent_path() / "LUI" / "Resources").string();
        } else {
            //打包模式下
            result = (exePath.parent_path() / "Resources").string();
        }
    }
    return result;
#else

#endif
};


std::string getExecutablePath() {
#if defined(_WIN32) || defined(_WIN64)
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    return std::string(path);
#elif defined(__linux__)
//    char path[PATH_MAX];
//    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
//    if (count != -1) {
//        return std::string(path, count);
//    }
//    return "";
#elif defined(__APPLE__)
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        return std::string(path);
    } else {
        return "";
    }
#else
    return "";
#endif
}
