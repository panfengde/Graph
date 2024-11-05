cmake_minimum_required(VERSION 3.18.0)
# 根据平台选择性加载配置文件
if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    # 加载安卓端配置
    message(STATUS "Configuring for Android platform")
    include(${CMAKE_SOURCE_DIR}/PlatformCmake/android.cmake)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows" OR ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" OR ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    # 加载 PC 端配置 (Windows, macOS, 或 Linux)
    message(STATUS "Configuring for PC platform")
    include(${CMAKE_SOURCE_DIR}/PlatformCmake/pc.cmake)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

