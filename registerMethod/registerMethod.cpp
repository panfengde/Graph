#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <iostream>
#include <vector>
#include <android/log.h>

#define LOG_TAG "OpenGLNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

AAssetManager *g_assetManager = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_pf_androidlui_MainActivity_nativeSetAssetManager(JNIEnv *env, jobject /* this */,
                                                       jobject assetManager) {
    g_assetManager = AAssetManager_fromJava(env, assetManager);
    if (!g_assetManager) {
        std::cerr << "Failed to obtain AAssetManager from Java." << std::endl;
    }
}

std::string readAssetFile(const char *filename) {
    if (g_assetManager == nullptr) {
        std::cerr << "AssetManager is not set!" << std::endl;
        return "";
    }

    AAsset *asset = AAssetManager_open(g_assetManager, filename, AASSET_MODE_STREAMING);
    if (asset == nullptr) {
        std::cerr << "Failed to open asset: " << filename << std::endl;
        return "";
    }
    // 读取文件内容
    off_t fileSize = AAsset_getLength(asset);
    std::vector<char> buffer(fileSize + 1);
    AAsset_read(asset, buffer.data(), fileSize);
    buffer[fileSize] = '\0'; // 确保字符串结尾
    //LOGI("%s", buffer.data());
    std::string readResult(buffer.data());
    //std::cout << "File contents: " << buffer.data() << std::endl; // 打印内容

    AAsset_close(asset);
    return readResult;
}


void CrossPlatformPrint(const std::string& message) {
#ifdef _WIN32
    // Windows 平台：使用 OutputDebugString 和 std::cout
    OutputDebugStringA(message.c_str());
    OutputDebugStringA("\n");
    std::cout << message << std::endl;
#elif defined(__APPLE__)
    // macOS 平台：使用 std::cout
    std::cout << message << std::endl;
#elif defined(__ANDROID__)
    // Android 平台：使用 __android_log_print
    __android_log_print(ANDROID_LOG_INFO, "CrossPlatformPrint", "%s", message.c_str());
#else
    // 其他平台（Linux等）：使用 std::cout
    std::cout << message << std::endl;
#endif
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_pf_androidlui_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

class AndroidLogStreambuf : public std::streambuf {
public:
    // 重载 overflow 函数
    int overflow(int c) override {
        if (c == '\n') {
            __android_log_print(ANDROID_LOG_INFO, "NativeLib", "%s", buffer.c_str());
            buffer.clear();
        } else {
            buffer += static_cast<char>(c);
        }
        return c;
    }
private:
    std::string buffer;  // 用于临时存储输出内容
};
AndroidLogStreambuf androidLogStreambuf;
std::ostream androidLogStream(&androidLogStreambuf);

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    std::cout.rdbuf(androidLogStream.rdbuf());  // 重定向 std::cout
    return JNI_VERSION_1_6;
}

